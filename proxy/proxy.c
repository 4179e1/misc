#if 0
${CC:=clang} $0 -o `basename $0 .c` -g -Wall
exit $?
#endif

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <signal.h>
#include <assert.h>

#define TCP_PROTO "tcp"
#define N_CLIENTS 5

int proxy_port; /* port to listen for proxy connections on */
struct sockaddr_in hostaddr; /* host addr assembled from gethostbyname */

extern int errno;
/* extern char *sys_errlist[]; */

void parse_args (int argc, char **argv);
void daemonize (int servfd);
void do_proxy(int usersockfd);
void reap_status (int signo);
void errorout (char *msg);

int main (int argc, char *argv[])
{
	socklen_t clilen;
	int childpid;
	int sockfd, newsockfd;
	struct sockaddr_in servaddr, cliaddr;

	parse_args (argc, argv);

	/* prepare an address struct to listen for connections */
	memset (&servaddr, 0, sizeof (servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl (INADDR_ANY);
	servaddr.sin_port = proxy_port;

	/* get a socket... */
	if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) < 0)
	{
		fputs ("failed to create server socket", stderr);
		exit (1);
	}
	
	/* ...and bind our address and port to it */
	if (bind (sockfd, (struct sockaddr *)(&servaddr), sizeof (servaddr)) < 0)
	{
		printf ("failed to bind server socket to specified port: %d, %s\n", htons(proxy_port), strerror (errno));
		exit (1);
	}

	/* get ready to accpet with N_CLIENTS waitting to connect */
	listen (sockfd, N_CLIENTS);

	/* turn ourselves into a daemon */
	//daemonize (sockfd);

	/* fall into a loop to accpet new connections and spawn children */
	while (1)
	{
		/* accpet the next connection */
		clilen = sizeof (struct sockaddr_in);
		newsockfd= accept (sockfd, (struct sockaddr *) (&cliaddr), &clilen);

		if ((newsockfd < 0) && (errno == EINTR))
		{
			continue;
		}
		else if (newsockfd < 0)
		{
			/* something quite amiss -- kill the server */
			errorout ("failed to accept connection");
		}

		/* fork a chlid to handle this connection */
		if ((childpid = fork ()) == 0)
		{
			close (sockfd);
			do_proxy (newsockfd);
			exit (0);
		}

		/* if fork() failed, this connection is silently dropped -- oope */
		close (newsockfd);
	}
}

void parse_args (int argc, char *argv[])
{
	int i;
	struct addrinfo *res;
	struct addrinfo hints = 
	{
		.ai_flags = AI_CANONNAME,
		.ai_family = AF_INET,
		.ai_socktype = SOCK_STREAM,
	};

	struct {
		char proxy_port[16];
		char isolated_host[65];
		char service_name[32];
	}pargs;

	if (argc < 4)
	{
		printf ("usage: %s <listen port> <isolated host> <service>\n", argv[0]);
		exit (1);
	}

	strncpy (pargs.proxy_port, argv[1], sizeof (pargs.proxy_port));
	strncpy (pargs.isolated_host, argv[2], sizeof (pargs.isolated_host));
	strncpy (pargs.service_name, argv[3], sizeof (pargs.service_name));

	for (i = 0; i < strlen (pargs.proxy_port); i++)
	{
		if (!isdigit (pargs.proxy_port[i]))
		{
			break;
		}
	}

	if (i == strlen (pargs.proxy_port))
	{
		proxy_port = htons (atoi (pargs.proxy_port));
	}
	else
	{
		printf ("%s: invalid proxy port", pargs.proxy_port);
		exit (0);
	}

	if (getaddrinfo (pargs.isolated_host, pargs.service_name, &hints, &res) != 0)
	{
		printf ("Unable to getaddrinfo for host: %s service: %s\n",pargs.isolated_host, pargs.service_name);
		exit (0);
	}

	memcpy (&hostaddr, res->ai_addr, res->ai_addrlen);

#if 1
	char address[INET_ADDRSTRLEN];
	assert (inet_ntop (res->ai_family, (void *)&(hostaddr.sin_addr), address, sizeof (address)) != NULL);
	printf ("address: %s port: %d\n", address, htons (hostaddr.sin_port));
#endif

	freeaddrinfo (res);

#if 0
	int ret;
	struct hostent *hostp;
	struct servent *servp;
	memset (&hostaddr, 0, sizeof (hostaddr));
	hostaddr.sin_family = AF_INET;

	if ((ret = inet_pton (AF_INET, pargs.isolated_host, &(hostaddr.sin_addr))) != 1)
	{
		if ((hostp = gethostbyname (pargs.isolated_host)) != NULL) /* FIXME: use getaddrinfo instead */
		{
			memcpy (&hostaddr.sin_addr, hostp->h_addr, hostp->h_length);
		}
		else
		{
			printf ("%s: unknown host", pargs.isolated_host);
			exit (1);
		}
	}

	if ((servp = getservbyname (pargs.service_name, TCP_PROTO)) != NULL)
	{
		hostaddr.sin_port = servp->s_port;
	}
	else if (atoi(pargs.service_name) > 0)
	{
		hostaddr.sin_port = htons (atoi (pargs.service_name));
	}
	else
	{
		printf ("%s: invalid/known service name or port number", pargs.service_name);
		exit (1);
	}
#endif

}

void daemonize (int servfd)
{
	int childpid, fd, fdtablesize;

	signal (SIGTTOU, SIG_IGN);
	signal (SIGTTIN, SIG_IGN);
	signal (SIGTSTP, SIG_IGN);

	if ((childpid = fork ()) < 0)
	{
		exit (1);
	}
	else if (childpid > 0)
	{
		exit (0); /* terminate parent, continue in child */
	}

	/* dissociate from process group */
#if _SVID_SOURCE || _XOPEN_SOURCE >= 500 || _XOPEN_SOURCE && _XOPEN_SOURCE_EXTENDED
	setpgrp();
#else
	if (setpgrp(0,getpid()) < 0)
	{
		fputs("failed to become process group leader",stderr);
		exit(1);
	}
#endif

	/* lose controlling terminal */
	if ((fd = open ("/dev/tty", O_RDWR)) >= 0)
	{
		ioctl (fd, TIOCNOTTY, NULL);
		close (fd);
	}

	for (fd = 0, fdtablesize = getdtablesize(); fd < fdtablesize; fd++)
	{
		if (fd != servfd)
		{
			close (fd);
		}
	}

	chdir ("/");

	umask (0);

	signal (SIGCHLD, reap_status);
}

void errorout (char *msg)
{
	FILE *console;

	console = fopen ("/dev/console", "a");
	fprintf (console, "proxyd: %s", msg);
	fclose (console);
	exit (1);
}

void reap_status (int signo)
{
	int pid;
	union wait status;

	while ((pid = wait3 (&status, WNOHANG, NULL)) > 0);
}

void do_proxy (int usersockfd)
{
	int isosockfd;
	fd_set rdfdset;
	int connstat;
	int iolen;
	char buf[2048];
	
	/* open a socket to connect to the isolated host */
	if ((isosockfd = socket (AF_INET, SOCK_STREAM, 0)) < 0)
	{
		errorout ("failed to create socket to host");
	}

	connstat = connect (isosockfd, (struct sockaddr *)&hostaddr, sizeof (hostaddr));

	switch (connstat)
	{
		case 0: 
			break;
		case ETIMEDOUT:
		case ECONNREFUSED:
		case ENETUNREACH:
			strcpy (buf, strerror (errno));
			strcat (buf, "/r/n");
			write (usersockfd, buf, strlen (buf));
			close (usersockfd);
			exit (1);
			break;
		default:
			errorout ("failed to connect to host");
	}

	while (1)
	{
		/* select for readbility on either of our two sockets */
		FD_ZERO (&rdfdset);
		FD_SET (usersockfd, &rdfdset);
		FD_SET (isosockfd, &rdfdset);

		if (select (FD_SETSIZE, &rdfdset, NULL, NULL, NULL) < 0)
		{
			errorout ("Select failed");
		}

		/* is the client sending data? */
		if (FD_ISSET(usersockfd, &rdfdset))
		{
			/* (zero length means the client disconnected */
			if ((iolen = read (usersockfd, buf, sizeof (buf))) <= 0)
			{
				break;
			}
			write (isosockfd, buf, iolen);
		}

		/* is the host sending data? */
		if (FD_ISSET (isosockfd, &rdfdset))
		{
			if ((iolen = read (isosockfd, buf, sizeof (buf))) <= 0)
			{
				break;
			}
			write (usersockfd, buf, iolen);
		}
	}
	close (isosockfd);
	close (usersockfd);


}
