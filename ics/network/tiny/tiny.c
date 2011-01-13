#if 0
gcc -Wall -o `basename $0 .c` $0 -lwp
exit
#endif
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <libwp.h>

#define MAXLINE 4096

void doit (int fd);
void read_requesthdrs (wp_rio_t *rp);
bool parse_uri (char *uri, char *filename, char *cgiargs);
void serve_static (int fd, char *filename, int filesize);
void get_filetype (char *filename, char *filetype);
void serve_dynamic (int fd, char *filename, char *cgiargs);
void clienterror (int fd, char *cause, char *errnum, char *stortmsg, char *longmsg);

int main (int argc, char *argv[])
{
	int listenfd, connfd, port;
	struct sockaddr_in clientaddr;
	socklen_t clientlen;

	if (argc != 2)
	{
		wp_critical ("usage: %s <port>\n", argv[0]);
	}

	port = atoi (argv[1]);

	listenfd = wp_open_listenfd (port);
	while (1)
	{
		clientlen = sizeof (clientaddr);
		connfd = wp_accept (listenfd, (struct sockaddr *)&clientaddr, &clientlen);
		doit (connfd);
		wp_close (connfd);
	}
}

#define MAXLINE 4096

void doit (int fd)
{
	bool is_static;
	struct stat sbuf;
	char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
	char filename[MAXLINE], cgiargs[MAXLINE];

	wp_rio_t *rio;

	rio = wp_rio_new (fd);
	wp_rio_readlineb (rio, buf, sizeof (buf));
	sscanf (buf, "%s %s %s", method, uri, version);

	if (strcasecmp (method, "GET") != 0)
	{
		clienterror (fd, method, "501", "not Implemented", "Tiny does not implement this method");
		return;
	}
	read_requesthdrs (rio);

	is_static = parse_uri (uri, filename, cgiargs);
	if (wp_stat(filename, &sbuf) < 0)
	{
		clienterror (fd, filename, "404", "Not found", "Tiny couldn't find this file");
		return;
	}

	if (is_static)
	{
		if (!(S_ISREG(sbuf.st_mode)) || !(S_IXUSR & sbuf.st_mode))
		{
			clienterror (fd, filename, "403", "Forbidden", "Tiny couldn't read the file");
			return;
		}
		serve_static (fd, filename, sbuf.st_size);
	}
	else
	{
		if (!(S_ISREG(sbuf.st_mode)) || !(S_IXUSR & sbuf.st_mode))
		{
			clienterror (fd, filename, "403", "Forbidden", "Tiny couldn't run the CGI program");
			return;
		}
		serve_dynamic (fd, filename, cgiargs);
	}
}

void clienterror (int fd, char *cause, char *errnum, char *shortmsg, char *longmsg)
{
	char buf[MAXLINE], body[MAXLINE];

	/* build the HTTP response body */
	sprintf (body, "<html><title>Tiny Error</title>");
	sprintf (body, "%s<body bgcolor=""ffffff"">\r\n", body);
	sprintf (body, "%s%s: %s\r\n", body, errnum, shortmsg);
	sprintf (body, "%s<p>%s: %s\r\n", body, longmsg, cause);
	sprintf (body, "%s<hr><em>The Tiny Web server</em>\r\n", body);

	/* print the HTTP response */
	sprintf (buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
	wp_writen (fd, buf, strlen (buf));
	sprintf (buf, "Content-type: text/html\r\n");
	wp_writen (fd, buf, strlen (buf));
	sprintf (buf, "Content-length: %d\r\n\r\n", strlen (body));
	wp_writen (fd, buf, strlen (buf));
	wp_writen (fd, body, strlen (body));
}

void read_requesthdrs (wp_rio_t *rp)
{
	char buf[MAXLINE];

	wp_rio_readlineb (rp, buf, MAXLINE);
	while (strcmp (buf, "\r\n"))
	{
		wp_rio_readlineb (rp, buf, MAXLINE);
	}
	return;
}

bool parse_uri (char *uri, char *filename, char *cgiargs)
{
	char *ptr;

	if (!strstr (uri, "cgi-bin")) /* static */
	{
		strcpy (cgiargs, "");
		strcpy (filename, ".");
		strcat (filename, uri);
		if (uri[strlen(uri) - 1] == '/')
		{
			strcat (filename, "home.html");
		}
		return true;
	}
	else	/* dynamic */
	{
		ptr = index (uri, '?');
		if (ptr) 
		{
			strcpy (cgiargs, ptr + 1);
			*ptr = '\0';
		}
		else
		{
			strcpy (cgiargs, "");
		}

		strcpy (filename, ".");
		strcat (filename, uri);
		return 0;
	}
}

void serve_static (int fd, char *filename, int filesize)
{
	int srcfd;
	char *srcp, filetype[MAXLINE], buf[MAXLINE];

	get_filetype (filename, filetype);
	sprintf (buf, "HTTP/1.0 200 OK\r\n");
	sprintf (buf, "%sServer: Tiny Web Server\r\n", buf);
	sprintf (buf, "%sContent-length: %d\r\n", buf, filesize);
	sprintf (buf, "%sContent-type: %s\r\n\r\n", buf, filetype);
	wp_writen (fd, buf, strlen (buf));

	srcfd = wp_open (filename, O_RDONLY, 0);
	srcp = wp_mmap (0, filesize, PROT_READ, MAP_PRIVATE, srcfd, 0);
	wp_close (srcfd);
	wp_writen (fd, srcp, filesize);
	wp_munmap (srcp, filesize);
}

void get_filetype (char *filename, char *filetype)
{
	if (strstr (filename, ".html"))
	{
		strcpy (filetype, "text/html");
	}
	else if (strstr (filename, ".gif"))
	{
		strcpy (filetype, "image/gif");
	}
	else if (strstr (filename, ".jpg"))
	{
		strcpy (filetype, "image/jpeg");
	}
	else
	{
		strcpy (filetype, "text/plain");
	}
}

void serve_dynamic (int fd, char *filename, char *cgiargs)
{
	char buf[MAXLINE];
	char *emptylist[] = {NULL};

	sprintf (buf, "HTTP/1.0 200 OK\r\n");
	wp_writen (fd, buf, strlen (buf));
	sprintf (buf, "Server: Tiny Web Server\r\n");
	wp_writen (fd, buf, strlen (buf));

	if (wp_fork () == 0)
	{
		setenv ("QUERY_STRING", cgiargs, 1);
		wp_dup2 (fd, STDOUT_FILENO);
		execve (filename, emptylist, __environ);
	}
	wp_wait (NULL);
}
