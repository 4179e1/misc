#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (void)
{
	pid_t pid;

	pid = fork ();
	if (pid < 0)
	{
		fprintf (stderr, "fork() error");
		exit (1);
	}
	else if (pid == 0)
	{
		/* child */
		printf ("child %d sleep for 60 seconds\n", getpid());
		sleep (60);
		printf ("child exit, will become zombie\n");
		exit (0);
	}

	/* parent */
	printf ("parent %d sleep for 600 seconds\n ", getpid());
	sleep (600);
	exit (0);
}
