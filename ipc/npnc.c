#include "util.h"
#include <wpmacros.h>
#include <wppthread.h>

#define NBUFF 10
#define MAXNTHREADS 100
int nitems, nproducers, nconsumers;

struct {
	int buff[NBUFF];
	int nput;
	int nputval;
	int nget;
	int ngetval;
	sem_t mutex, nempty, nstored;
} shared;

void *produce (void *arg)
{
	while (1)
	{
		wp_sem_wait (&shared.nempty);
		wp_sem_wait (&shared.mutex);

		if (shared.nput >= nitems)
		{
			wp_sem_post (&shared.nstored);	
			wp_sem_post (&shared.nempty);
			wp_sem_post (&shared.mutex);
			return NULL;
		}

		shared.buff[shared.nput % NBUFF] = shared.nputval;
		shared.nput++;
		shared.nputval++;

		wp_sem_post (&shared.mutex);
		wp_sem_post (&shared.nstored);
		*((int *) arg) += 1;
	}
	return NULL;
}

void *consume (void *arg)
{
	int i;
	while (1)
	{
		wp_sem_wait (&shared.nstored);
		wp_sem_wait (&shared.mutex);
		
		if (shared.nget >= nitems)
		{
			wp_sem_post (&shared.nstored);
			wp_sem_post (&shared.mutex);
			return NULL;
		}

		i = shared.nget % NBUFF;
		if (shared.buff[i] != shared.ngetval)
			wp_message ("error: buff[%d] = %d\n", i, shared.buff[i]);

		shared.nget++;
		shared.ngetval++;

		wp_sem_post (&shared.mutex);
		wp_sem_post (&shared.nempty);
		* ((int *)arg) += 1;
	}

	return NULL;
}

int main (int argc, char *argv[])
{
	int i, prodcount[MAXNTHREADS], conscount[MAXNTHREADS];
	pthread_t tid_produce[MAXNTHREADS], tid_consume[MAXNTHREADS];
	if (argc != 4)
		wp_critical ("usage: %s <#items> <#producers> <#consumers>", argv[0]);

	wp_set_exit_level (WP_LOG_WARNING);

	nitems = atoi (argv[1]);
	nproducers = WP_MIN (atoi(argv[2]), MAXNTHREADS);
	nconsumers = WP_MIN (atoi(argv[3]), MAXNTHREADS);

	wp_sem_init (&shared.mutex, 0, 1);
	wp_sem_init (&shared.nempty, 0, NBUFF);
	wp_sem_init (&shared.nstored, 0, 0);

	for (i = 0; i < nproducers; i++)
	{
		prodcount[i] = 0;
		wp_pthread_create (&tid_produce[i], NULL, produce, &prodcount[i]);
	}

	for (i = 0; i < nconsumers; i++)
	{
		conscount[i] = 0;
		wp_pthread_create (&tid_consume[i], NULL, consume, &conscount[i]);
	}

	for (i = 0; i < nproducers; i++)
	{
		wp_pthread_join (tid_produce[i], NULL);
		wp_message ("producer count[%d] = %d\n", i, prodcount[i]);
	}

	for (i = 0; i < nconsumers; i++)
	{
		wp_pthread_join (tid_consume[i], NULL);
		wp_message ("consumer count[%d] = %d\n", i, conscount[i]);
	}

	wp_sem_destroy (&shared.mutex);
	wp_sem_destroy (&shared.nempty);
	wp_sem_destroy (&shared.nstored);

	return 0;
}
