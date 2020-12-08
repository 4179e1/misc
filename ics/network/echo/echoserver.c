#include "echo.h"


int main(int argc, char **argv) 
{
	int listenfd, connfd, port;
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

	while (1) {
		clientlen = sizeof(clientaddr);
		connfd = wp_accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);

		/* determine the domain name and IP address of the client */
		hp = wp_gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr, 
				sizeof(clientaddr.sin_addr.s_addr), AF_INET);
		wp_inet_ntop(AF_INET, &clientaddr.sin_addr, haddrp, sizeof (haddrp));
		printf("server connected to %s (%s)\n", hp->h_name, haddrp);

		echo(connfd);
		wp_close(connfd);
	}
	exit(0);
}
/* $end echoserverimain */
