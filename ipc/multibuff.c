#include "util.h"
#include <wppthread.h>

#define NBUFF 8
#define BUFFSIZE 4096

struct {
	struct {
		char data[BUFFSIZE];
		ssize_t n;
	} buff[NBUFF];
	sem_t mutex, nempty, nstored;
} shared;

int fd;

void *produce (void *arg)
{
	int i;
	for (i = 0;;)
	{
		wp_sem_wait (&shared.nempty);

		wp_sem_wait (&shared.mutex);
		/* critical region, for illustion only */
		wp_sem_post (&shared.mutex);

		shared.buff[i].n = wp_read (fd, shared.buff[i].data, BUFFSIZE);
		if (shared.buff[i].n == 0)
		{
			wp_sem_post (&shared.nstored);
			return NULL;
		}
		if (++i >= NBUFF)
			i = 0;

		wp_sem_post (&shared.nstored);
	}

	return NULL;
}


void *consume (void *arg)
{
	int i;
	for (i = 0;;)
	{
		wp_sem_wait (&shared.nstored);

		wp_sem_wait (&shared.mutex);
		/* critical region */
		wp_sem_post (&shared.mutex);

		if (shared.buff[i].n == 0)
			return NULL;

		wp_write (STDOUT_FILENO, shared.buff[i].data, shared.buff[i].n);
		if (++i >= NBUFF)
			i = 0;

		wp_sem_post (&shared.nempty);
	}

	return NULL;
}


int main (int argc, char *argv[])
{
	pthread_t tid_produce, tid_consume;

	if (argc != 2)
		wp_critical ("usage: %s <pathname>");
	
	fd = wp_open (argv[1], O_RDONLY, 0);

	wp_sem_init (&shared.mutex, 0, 1);
	wp_sem_init (&shared.nempty, 0, NBUFF);
	wp_sem_init (&shared.nstored, 0, 0);

	wp_pthread_create (&tid_produce, NULL, produce, NULL);
	wp_pthread_create (&tid_consume, NULL, consume, NULL);

	wp_pthread_join (tid_produce, NULL);
	wp_pthread_join (tid_consume, NULL);

	wp_sem_destroy (&shared.mutex);
	wp_sem_destroy (&shared.nempty);
	wp_sem_destroy (&shared.nstored);

	return 0;
}
