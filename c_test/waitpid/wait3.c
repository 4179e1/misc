#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char *argv[])
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
		pid_t ppid;
		ppid = fork ();
		if (ppid < 0)
		{
			fprintf (stderr, "fork() error\n");
			exit (1);
		}
		else if (ppid > 0)
		{
			exit(exit_code);
		}

		printf ("child of child (orphan) sleep for 60 seconds\n");
		sleep (60);
		printf ("child of child (orphan) exited, no more zombie there\n");

		exit (0);
	}

	int status;
	if (waitpid (pid, &status, 0) != pid)
	{
		fprintf (stderr, "waitpid() error\n");
		exit (1);
	}
	else
	{
		printf ("child exited %d\n", WEXITSTATUS(status));
	}

	/* parent */
	printf ("parent %d sleep for 600 seconds\n ", getpid());
	sleep (600);
	exit (0);
}
