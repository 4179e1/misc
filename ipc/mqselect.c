#include <mqueue.h>
#include <sys/select.h>
#include "util.h"

int pipefd[2];
static void sig_usr1(int);

static void sig_usr1 (int signo)
{
	wp_write (pipefd[1], "", 1);
}

int main (int argc, char *argv[])
{
	int nfds;
	char c;
	fd_set rset;
	mqd_t mqd;
	ssize_t n;
	struct mq_attr attr;
	struct sigevent sigev;

	if (argc != 2)
		wp_critical ("usage: %s <name>", argv[0]);

	mqd = mq_open (argv[1], O_RDONLY | O_NONBLOCK);
	if (mqd == -1)
		wp_critical ("mq_open() failed: %s", strerror (errno));

	if (mq_getattr (mqd, &attr) == -1)
		wp_critical ("mq_getattr() failed: %s", strerror (errno));

	char buff[attr.mq_msgsize];
	
	wp_pipe (pipefd);

	wp_signal (SIGUSR1, sig_usr1);
	sigev.sigev_notify = SIGEV_SIGNAL;
	sigev.sigev_signo = SIGUSR1;
	if (mq_notify (mqd, &sigev) == -1)
		wp_critical ("mq_notify() failed: %s", strerror (errno));

	FD_ZERO (&rset);

	while (1)
	{
		FD_SET(pipefd[0], &rset);
		nfds = select (pipefd[0] + 1, &rset, NULL, NULL, NULL);

		if (FD_ISSET (pipefd[0], &rset))
		{
			wp_read (pipefd[0], &c, 1);
			if (mq_notify (mqd, &sigev) == -1)
				wp_critical ("mq_notify() failed: %s", strerror (errno));

			while ((n = mq_receive (mqd, buff, attr.mq_msgsize, NULL)) >= 0)
				wp_message ("read %ld bytes\n", (long) n);

			if (errno != EAGAIN)
				wp_critical ("mq_recevive() failed %s", strerror (errno));
		}
	}

	exit (0);

}

