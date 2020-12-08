#if  0
${CC=clang} -o `basename $0 .c` -Wall $0 `pkg-config --libs --cflags libwp0 `
exit 0
#endif
#include <errno.h>
#include <stdlib.h>
#include <wpmacros.h>
#include "web.h"

struct addrinfo *
Host_serv(const char *host, const char *serv, int family, int socktype)
{
	int				n;
	struct addrinfo	hints, *res;

	bzero(&hints, sizeof(struct addrinfo));
	hints.ai_flags = AI_CANONNAME;	/* always return canonical name */
	hints.ai_family = family;		/* 0, AF_INET, AF_INET6, etc. */
	hints.ai_socktype = socktype;	/* 0, SOCK_STREAM, SOCK_DGRAM, etc. */

	if ( (n = getaddrinfo(host, serv, &hints, &res)) != 0)
		wp_critical ("host_serv error for %s, %s: %s",
				 (host == NULL) ? "(no hostname)" : host,
				 (serv == NULL) ? "(no service name)" : serv,
				 gai_strerror(n));

	return(res);	/* return pointer to first on linked list */
}

int main (int argc, char *argv[])
{
	int i, fd, n, maxnconn, flags, error;
	char buf[MAXLINE];
	fd_set rs, ws;

	if (argc < 5)
		wp_critical ("usage web <#conns> <hostname> <homepage> <file1> ...");
	maxnconn = atoi (argv[1]);
	nfiles = WP_MIN (argc - 4, MAXFILES);

	for (i = 0; i < nfiles; i++)
	{
		file[i].f_name = argv[ i + 4 ];
		file[i].f_host = argv[2];
		file[i].f_flags = 0;
	}

	home_page (argv[2], argv[3]);

	FD_ZERO (&rset);
	FD_ZERO (&wset);
	maxfd = -1;
	nlefttoread = nlefttoconn = nfiles;
	nconn = 0;
	socklen_t nlen = 0;

	while (nlefttoread > 0)
	{
		while ((nconn < maxnconn) && (nlefttoconn > 0))
		{
			/* find file to read */
			for (i = 0; i < nfiles; i++)
			{
				if (file[i].f_flags == 0)
				{
					break;
				}
			}
			if (i == nfiles)
			{
				wp_critical ("nlefttoconn = %d but nothing found", nlefttoconn);
			}
			start_connect (&file[i]);
			nconn++;
			nlefttoconn--;
		}

		rs = rset;
		ws = rset;
		n = wp_select (maxfd + 1, &rs, &ws, NULL, NULL);
		for (i = 0; i < nfiles; i++)
		{
			flags = file[i].f_flags;
			if ((flags == 0) ||(flags & F_DONE))
			{
				continue;
			}
			fd=file[i].f_fd;
			if ((flags & F_CONNECTING) && (FD_ISSET(fd, &rs) || FD_ISSET (fd, &ws)))
			{
				nlen = (socklen_t) sizeof (error);
				if (getsockopt (fd, SOL_SOCKET, SO_ERROR, &error, &nlen) < 0 || (error != 0))
				{
					wp_critical ("nonblocking connect failed for %s", file[i].f_name);
				}

				/* connection established */
				printf ("connection established for %s\n", file[i].f_name);
				FD_CLR (fd, &wset);	/* no more writeableility test */
				write_get_cmd (&file[i]); /* write the GET command */
			}
			else if (flags &F_READING&& FD_ISSET (fd, &rs))
			{
				if ((n = wp_read (fd, buf, sizeof (buf))) == 0)
				{
					printf ("end-of-file on %s\n", file[i].f_name);
					close (fd);
					file[i].f_flags = F_DONE;
					FD_CLR (fd, &rset );
					nconn--;
					nlefttoread--;
				}
				else
				{
					printf ("read %d bytes from %s\n", n, file[i].f_name);
				}
			}
		}
	}
	exit (0);
}

void home_page (const char *host, const char *fname)
{
	int fd, n;
	char line[MAXLINE];

	fd = wp_open_clientfd (host, SERV); /* blocking connect() */
	n = snprintf (line, sizeof (line), GET_CMD, fname);
	wp_writen (fd, line, n);
	for (;;)
	{
		if ((n = wp_read (fd, line, MAXLINE)) == 0)
		{
			break; /*server closed connection */
		}
		printf ("read %d bytes of home page\n", n);

		/* do whatever with data */
	}
	printf ("end-of-file on home page\n");
	close (fd);
}

void start_connect (struct file *fptr)
{
	int fd, n;
	struct addrinfo *ai;

	ai = Host_serv (fptr->f_host, "www", 0 , SOCK_STREAM);
	fd = wp_socket (ai->ai_family, ai->ai_socktype, ai->ai_protocol);
	fptr->f_fd = fd;
	printf ("start_connect for %s, fd %d\n", fptr->f_name, fd);
	/* set socket nonblocking */
	wp_fd_set_flag (fd, O_NONBLOCK);
	/* initiate nonblocking connect to the server */
	if ((n = connect (fd, ai->ai_addr, ai->ai_addrlen )) < 0)
	{
		if (errno != EINPROGRESS)
		{
			wp_critical ("nonblocking connect error");
		}
		fptr->f_flags = F_CONNECTING;
		FD_SET(fd, &rset); /* select for reading and writing */
		FD_SET (fd, &wset);
		if (fd > maxfd)
			maxfd = fd;
	}
	else if (n >= 0) /* connect is already done */
	{
		write_get_cmd (fptr);
	}
}

void write_get_cmd (struct file *fptr)
{
	int n;
	char line[MAXLINE];

	n = snprintf (line, sizeof (line), GET_CMD, fptr->f_name);
	wp_writen (fptr->f_fd, line, n);
	printf ("wrote %d bytes for %s\n", n, fptr->f_name);
	fptr->f_flags = F_READING; /* clears F_CONNECTING */
	FD_SET (fptr->f_fd, &rset); /* will read server's reply */
	if (fptr->f_fd > maxfd)
	{
		maxfd = fptr->f_fd;
	}
}
