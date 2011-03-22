#include <libwp.h>
#include <wppthread.h>
#include "echo.h"

void *thread (void *vargp)
{
	int connfd = *(int *)vargp;

	wp_pthread_detach (pthread_self ());
	free (vargp);
	echo (connfd);
	wp_close (connfd);

	return NULL;
}

int main (int argc, char *argv[])
{
	int listenfd, *connfdp, port;
	socklen_t clientlen = sizeof (struct sockaddr_in);
	struct sockaddr_in clientaddr;
	pthread_t tid;

	if (argc != 2)
	{
		wp_critical ("usage: %s <port>\n", argv[0]);
	}

	port = atoi (argv[1]);

	listenfd = wp_open_listenfd (port);
	if (listenfd < 0)
	{
		wp_critical ("error");
	}

	while (1)
	{
		connfdp = wp_malloc (sizeof (int));
		*connfdp = wp_accept (listenfd, (struct sockaddr *)&clientaddr, &clientlen);
		wp_pthread_create (&tid, NULL, thread, connfdp);
	}
}

