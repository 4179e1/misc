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

#define MAXNCLI 32
int clifd[MAXNCLI], iget, iput;
pthread_mutex_t clifd_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t clifd_cond = PTHREAD_COND_INITIALIZER;
int nthreads;

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
	wp_message ("Thread %d starting", (int) arg);

	while (1)
	{
		pthread_mutex_lock (&clifd_mutex);
		while (iget == iput)
			pthread_cond_wait (&clifd_cond, &clifd_mutex);
		connfd = clifd[iget];
		if (++iget == MAXNCLI)
			iget = 0;
		wp_pthread_mutex_unlock (&clifd_mutex);
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
	int i, listenfd, connfd;
	socklen_t clilen, addrlen = sizeof (struct sockaddr);
	struct sockaddr *cliaddr;

	if (argc < 3)
		wp_critical ("usage: %s <port#> <#thread>", argv[0]);
	
	cliaddr = wp_malloc (addrlen);
	nthreads = atoi (argv[2]);
	tptr = wp_calloc (nthreads, sizeof (Thread));
	iput = iget = 0;

	listenfd = wp_open_listenfd (atoi(argv[1]));

	for (i = 0; i < nthreads; i++)
		thread_make (i);

	wp_signal (SIGINT, sigint_handler);;

	while (1)
	{
		clilen = addrlen;
		connfd = wp_accept (listenfd, cliaddr, &clilen);
		wp_pthread_mutex_lock (&clifd_mutex);
		clifd[iput] = connfd;
		if (++iput == MAXNCLI)
			iput = 0;

		if (iput == iget)
			wp_critical ("iput = iget = %d", iput);
		wp_pthread_cond_signal (&clifd_cond);
		wp_pthread_mutex_unlock (&clifd_mutex); 
	} 
}
