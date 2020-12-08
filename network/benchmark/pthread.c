#include <libwp.h>
#include <wppthread.h>
#include <stdlib.h>
#include "lib.h"

#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"

void *doit (void *arg)
{
	wp_pthread_detach (pthread_self());
	web_child((int) arg);
	close ((int) arg);
	return (NULL);
}

int main (int argc, char *argv[])
{
	int listenfd, connfd;
	pthread_t tid;
	socklen_t clilen, addrlen = sizeof (struct sockaddr);
	struct sockaddr *cliaddr;

	if (argc < 2)
		wp_critical ("usage: %s <port#>", argv[0]);

	listenfd = wp_open_listenfd (atoi (argv[1]));
	cliaddr = wp_malloc (addrlen);
	wp_signal (SIGINT, sig_int);

	while (1)
	{
		clilen = addrlen;
		connfd = wp_accept (listenfd, cliaddr, &clilen);
		/* connfd: it would be a problem on the platfroms that pointer is shorter than integer */
		wp_pthread_create (&tid, NULL, doit, (void *)connfd);
	}
}

