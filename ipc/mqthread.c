#include <mqueue.h>
#include <pthread.h>
#include "util.h"

mqd_t mqd;
struct mq_attr attr;

struct sigevent sigev;
static void notify_thread (union sigval arg)
{
	ssize_t n;
	char buff[attr.mq_msgsize];

	wp_message ("notify_thread started\n");

	if (mq_notify(mqd, &sigev) == -1)
		wp_critical ("mq_notify() failed: %s", strerror (errno));

	while ((n = mq_receive (mqd, buff, attr.mq_msgsize, NULL)) >= 0)
		wp_message ("read %ld bytes\n", (long) n);

	if (errno != EAGAIN)
		wp_critical ("mq_receive error");

	pthread_exit (NULL);
}

int main (int argc, char *argv[])
{
	if (argc != 2)
		wp_critical ("usage: mqthread <name>");
	
	mqd = mq_open (argv[1], O_RDONLY | O_NONBLOCK);
	if (mq_getattr (mqd, &attr) == -1)
		wp_critical ("mq_getattr() failed: %s", strerror(errno));

	sigev.sigev_notify = SIGEV_THREAD;
	sigev.sigev_value.sival_ptr = NULL;
	sigev.sigev_notify_function = notify_thread;
	sigev.sigev_notify_attributes = NULL;

	if (mq_notify (mqd, &sigev) == -1)
		wp_critical ("mq_notify() failed: %s", strerror(errno));

	while (1)
		pause();

	return 0;
}
