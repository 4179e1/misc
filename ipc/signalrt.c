#include "util.h"

static void sig_rt (int signo, siginfo_t *info, void *context)
{
	printf ("received signal #%d, code = %d, ival = %d\n",
		signo, info->si_code, info->si_value.sival_int);
}

int main (int argc, char *argv[])
{
	int i, j;
	pid_t pid;
	sigset_t newset;
	union sigval val;

	printf ("SIGRTMIN = %d, SIGRTMAX = %d\n", (int)SIGRTMIN, (int)SIGRTMAX);

	if ((pid = wp_fork())== 0)
	{
		wp_sigemptyset (&newset);
		wp_sigaddset (&newset, SIGRTMAX);
		wp_sigaddset (&newset, SIGRTMAX - 1);
		wp_sigaddset (&newset, SIGRTMAX - 2);
		wp_sigprocmask (SIG_BLOCK, &newset, NULL);

		signal_rt (SIGRTMAX, sig_rt, &newset);
		signal_rt (SIGRTMAX - 1, sig_rt, &newset);
		signal_rt (SIGRTMAX - 2, sig_rt, &newset);

		sleep (6);

		wp_sigprocmask (SIG_UNBLOCK, &newset, NULL);

		sleep (3);
		exit (0);
	}

	sleep (3);
	for (i = SIGRTMAX; i >= SIGRTMAX -2 ; i--)
	{
		for (j = 0; j <= 2; j++)
		{
			val.sival_int = j;
			sigqueue (pid, i, val);
			printf ("sent signal %d, val = %d\n", i, j);
		}
	}
	exit (0);
}
