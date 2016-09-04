#include <libwp.h>
#include <wppthread.h>
#include <stdlib.h>
#include "lib.h"

#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"

typedef struct {
	pthread_t thread_tid;
	long thread_count;
} Thread;
Thread *tptr;

int listenfd, nthreads;
socklen_t addrlen = sizeof (struct sockaddr);
pthread_mutex_t tlock = PTHREAD_MUTEX_INITIALIZER;

static void sigint_handler (int signo)
{
	int i;
	for (i = 0; i < nthreads; i++)
	{
		wp_pthread_cancel (tptr[i].thread_tid);
		wp_message ("Thread %d accepted %ld connections\n", tptr[i].thread_tid, tptr[i].thread_count);
	}

	pr_cpu_time ();
	exit (0);
}


void *thread_main (void *arg)
{
	int connfd;
	socklen_t clilen; 
	struct sockaddr *cliaddr;

	cliaddr = wp_malloc (addrlen);
	wp_message ("Thread %d starting", (int) arg);

	while (1)
	{
		clilen = addrlen;
		wp_pthread_mutex_lock (&tlock);
		connfd = wp_accept (listenfd, cliaddr, &clilen);
		wp_pthread_mutex_unlock (&tlock);
		tptr[(int) arg].thread_count++;
		web_child (connfd);
		wp_close (connfd);
	}
}

void thread_make (int i)
{
	wp_pthread_create (&tptr[i].thread_tid, NULL, &thread_main, (void *)i);
	return;
}

int main (int argc, char *argv[])
{
	int i;
	if (argc < 3)
		wp_critical ("usage: %s <port#> <#thread>", argv[0]);
	
	nthreads = atoi (argv[2]);
	tptr = wp_calloc (nthreads, sizeof (Thread));

	listenfd = wp_open_listenfd (atoi(argv[1]));

	for (i = 0; i < nthreads; i++)
		thread_make (i);

	wp_signal (SIGINT, sigint_handler);;

	while (1)
		pause();
}
