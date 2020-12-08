#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sig_usr (int signo)
{
	switch (signo) 
	{
		case SIGUSR1:
			printf ("received SIGUSR1\n");
			break;
		case SIGUSR2:
			printf ("received SIGUSR2\n");
			break;
		case SIGTERM:
			printf ("received SIGTERM, I won't quit\n");
			break;
		default:
			printf ("wtf?\n");
			break;
	}
}

int main (void)
{
	signal (SIGUSR1, sig_usr);
	signal (SIGUSR2, sig_usr);
	signal (SIGTERM, sig_usr);

	for (;;)
		pause();

	return (0);
}

