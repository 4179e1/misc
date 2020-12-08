#include <stdlib.h>
#include <libwp.h>
#include "echo.h"

void command (void)
{
	char buf[MAXLINE];
	if (!wp_fgets (buf, sizeof (buf), stdin))
	{
		wp_critical ("command error");
	}

	printf ("%s", buf);
}

int main (int argc, char *argv[])
{
	int listenfd, connfd, port;
	socklen_t clientlen = sizeof (struct sockaddr_in);
	struct sockaddr_in clientaddr;
	fd_set read_set, ready_set;

	if (argc != 2)
	{
		wp_critical ("usage: %s <port>", argv[0]);
	}

	port = atoi (argv[1]);
	listenfd = wp_open_listenfd (port);
	if (listenfd < 0)
	{
		wp_critical ("error exit");
	}

	FD_ZERO (&read_set);
	FD_SET(STDIN_FILENO, &read_set);
	FD_SET(listenfd, &read_set);

	while (1) {
		ready_set = read_set;
		wp_select (listenfd + 1, &ready_set, NULL, NULL, NULL);
		if (FD_ISSET(STDIN_FILENO, &ready_set))
		{
			command ();
		}
		if (FD_ISSET(listenfd, &ready_set))
		{
			connfd = wp_accept (listenfd, (struct sockaddr *)&clientaddr, &clientlen);
			echo (connfd);
		}
	}
}
