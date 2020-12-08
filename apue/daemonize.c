#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <sys/stat.h>

void daemonize (const char *cmd)
{
	int 				i, fd0, fd1, fd2;
	pid_t 				pid;
	struct rlimit		rl;
	struct sigaction	sa;

	umask (0);

	if (getrlimit (RLIMIT_NOFILE, &rl) < 0)
	{
		fprintf (stderr, "getrlimit() error\n");
		exit (1);
	}

	if ((pid = fork()) < 0)
	{
		fprintf (stderr, "fork() error\n");
		exit (1);
	}
	else if (pid != 0)
	{
		printf ("p1 quit\n");
		exit (0);
	}
	setsid();
	
	sa.sa_handler = SIG_IGN;
	sigemptyset (&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction (SIGHUP, &sa, NULL) < 0)
	{
		fprintf (stderr, "sigaction() error\n");
		exit (1);
	}
	if ((pid == fork ()) < 0)
	{
		fprintf (stderr, "fork() error\n");
		exit (1);
	}
	else if (pid != 0)
	{
		exit (0);
	}

	if (chdir("/") < 0)
	{
		fprintf (stderr, "chdir() error\n");
		printf ("p2 quit\n");
		exit (0);
	}

	if (rl.rlim_max == RLIM_INFINITY)
	{
		rl.rlim_max = 1024;
	}
	for (i = 0; i < rl.rlim_max; i++)
	{
		close (i);
	}

	fd0 = open ("dev/null", O_RDWR);
	fd1 = dup (0);
	fd2 = dup (0);

	openlog (cmd, LOG_CONS, LOG_DAEMON);
	if (fd0 != 0 || fd1 != 1 || fd2 != 2)
	{
		syslog (LOG_ERR, "unexpected file descriptors %d, %d, %d", fd0, fd1, fd2);
		exit (1);
	}

}

int main (void)
{
	daemonize ("no_such_command");
	sleep (10);

	return 0;
}
