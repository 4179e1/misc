#include <stdbool.h>
#include <errno.h>
#include <sys/wait.h>
#include "echo.h"

static bool keep_on_running = true;
static int listenfd;

void sigchld_handler (int sig)
{
	while (waitpid (-1, 0, WNOHANG) > 0)
		;
	return;
}

void sigterm_handler (int sig)
{
	keep_on_running = false;
	wp_close (listenfd);
}


int main(int argc, char **argv) 
{
	int connfd, port;
	socklen_t clientlen;
	struct sockaddr_in clientaddr;
	struct hostent *hp;
	char haddrp[INET_ADDRSTRLEN];
	if (argc != 2)
	{
		wp_critical("usage: %s <port>\n", argv[0]);
	}
	port = atoi(argv[1]);

	listenfd = wp_open_listenfd(port);
	if (listenfd < 0)
	{
		wp_critical ("open listenfd error");
	}

	wp_signal (SIGCHLD, sigchld_handler);
	wp_signal (SIGTERM, sigterm_handler);

	wp_debug_full (stdout, "My pid is %d", getpid());
	while (1) {
		clientlen = sizeof(clientaddr);
		errno = 0;
		connfd = wp_accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
		wp_debug("connfd: %d errno: %d", connfd, errno);
		if (keep_on_running == false)
		{
			break;
		}

		if (wp_fork () == 0)
		{
			wp_close (listenfd);
			/* determine the domain name and IP address of the client */
			hp = wp_gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr, 
					sizeof(clientaddr.sin_addr.s_addr), AF_INET);
			wp_inet_ntop(AF_INET, &clientaddr.sin_addr, haddrp, sizeof (haddrp));
			printf("server connected to %s (%s)\n", hp->h_name, haddrp);

			echo(connfd);
			
			wp_close (connfd);
			exit (0);
		}
		wp_close(connfd);
	}
	exit(0);
}
/* $end echoserverimain */

