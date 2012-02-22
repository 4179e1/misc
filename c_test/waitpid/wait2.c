#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char *argv[1])
{
	pid_t pid;
	int exit_code = 0;

	if (argc >= 2)
	{
		exit_code = atoi (argv[1]);
	}
	printf ("child exit status should be %d\n", exit_code);

	pid = fork ();
	if (pid < 0)
	{
		fprintf (stderr, "fork() error\n");
		exit (1);
	}
	else if (pid == 0)
	{
		/* child */
		printf ("child %d sleep for 60 seconds\n", getpid());
		sleep (60);
		exit (exit_code);
	}

	/* parent */
	int status;
	if (waitpid (pid, &status, 0) != pid)
	{
		fprintf (stderr, "waitpid() error\n");
		exit (1);
	}
	else
	{
		printf ("child exited %d, no more zombie\n", WEXITSTATUS(status));
	}
	printf ("parent %d sleep for 600 seconds\n ", getpid());
	sleep (600);
	exit (0);
}
