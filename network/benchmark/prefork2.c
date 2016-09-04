#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <libwp.h>
#include "lib.h"

long  *cptr;
static int nchildren;
static pid_t *pids;

long *meter (int nchildren)
{
	long *ptr;
	ptr = wp_mmap (0, nchildren * sizeof (long), PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
	return ptr;
}

static void sigint_handler (int signo)
{
	int i;
	for (i = 0; i < nchildren; i++)
	{
		kill (pids[i], SIGTERM);
		wp_message ("child %d accepted %ld connections\n", pids[i], cptr[i]);
	}

	  while (wait (NULL) > 0)
	  	;

	if (errno != ECHILD)
		wp_critical ("wait() error");


	pr_cpu_time ();
	exit (0);
}

static void child_main (int i, int listenfd, int addrlen)
{
	int connfd;
	socklen_t clilen;
	struct sockaddr *cliaddr;
	cliaddr = wp_malloc (addrlen);
	wp_message ("child %ld starting\n", (long) getpid());
	while (1)
	{
		clilen = addrlen;
		connfd = wp_accept (listenfd, cliaddr, &clilen);
		cptr[i]++;
		web_child (connfd);
		wp_close (connfd);
	}
}

static pid_t child_make (int i, int listenfd, int addrlen)
{
	pid_t pid;
	if ((pid = wp_fork ()) > 0)
		return (pid);			/* parent */

	cptr[i] = 0;
	child_main (i, listenfd, addrlen);
	return 0; /* to get rid of compiler warning */
}


int main (int argc, char *argv[])
{
	int listenfd, i;
	socklen_t addrlen = sizeof (struct sockaddr);

	if (argc < 3)
		wp_critical ("usag: %s <port#> <#children>", argv[0]);
	
	listenfd = wp_open_listenfd (atoi(argv[1]));

	nchildren = atoi (argv[2]);

	cptr = meter (nchildren);
	pids = wp_calloc (nchildren, sizeof (pid_t));
	for (i = 0; i < nchildren; i++)
		pids[i] = child_make (i, listenfd, addrlen);

	signal (SIGINT, sigint_handler);

	while (1)
		pause();

	return 0;
}


