#include <libwp.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include "lib.h"

int main (int argc, char *argv[])
{
	int listenfd, connfd;
	pid_t childpid;

	socklen_t clilen, addrlen;
	struct sockaddr *cliaddr;

	addrlen = sizeof (struct sockaddr);

	if (argc < 2)
		wp_critical ("usage: %s <port#>", argv[0]);
	listenfd = wp_open_listenfd (atoi(argv[1]));
	
	cliaddr = wp_malloc (addrlen);
	wp_signal (SIGCHLD, sig_chld);
	wp_signal (SIGINT, sig_int);
	
	while (1)
	{
		clilen = addrlen;
		if ((connfd = wp_accept (listenfd, cliaddr, &clilen)) < 0)
		{
			printf ("%d accepted a connection\n", getpid());
			if (errno == EINTR)
				continue;
			else 
				wp_critical ("accept() error");
		}

		if ((childpid = wp_fork()) == 0)
		{
			/* child */
			close (listenfd);
			web_child(connfd);
			wp_debug ("child %d done", childpid);
			exit(0);
		}
		close (connfd);
	}
}
