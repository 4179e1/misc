#include "util.h"
#include <wppthread.h>
#include <wpmacros.h>

#define MAXNITEMS 1000000
#define MAXNTHREADS 100

int nitems;
int buff[MAXNITEMS];

int nsignal = 0;

struct {
	pthread_mutex_t mutex;
	int nput;				/* next index to store */
	int nval;				/* next vbalue toi store */
} put = {
	PTHREAD_MUTEX_INITIALIZER,
};

struct {
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	int nready;
} nready = {
	PTHREAD_MUTEX_INITIALIZER,
	PTHREAD_COND_INITIALIZER,
};

void * produce (void *arg)
{
	while (1)
	{
		wp_pthread_mutex_lock (&put.mutex);
		if (put.nput >= nitems) 
		{
			wp_pthread_mutex_unlock (&put.mutex);
			return NULL;				/* already full */
		}

		buff[put.nput] = put.nval;
		put.nput++;
		put.nval++;
		wp_pthread_mutex_unlock (&put.mutex);

		wp_pthread_mutex_lock (&nready.mutex);
		/* notify consumer only if the array were empty, cuz we've just put an item */
		if (nready.nready == 0)
		{
			wp_pthread_cond_signal (&nready.cond);
			nsignal++;
		}
		nready.nready++;
		wp_pthread_mutex_unlock (&nready.mutex);
		*((int *)arg) += 1;
	}
}

void * consume (void *arg)
{
	int i;
	for (i = 0; i< nitems; i++)
	{
		wp_pthread_mutex_lock (&nready.mutex);
		/* wait if the array were emptry */
		while (nready.nready == 0)
			wp_pthread_cond_wait (&nready.cond, &nready.mutex);
		nready.nready--;
		wp_pthread_mutex_unlock (&nready.mutex);

		if (buff[i] != i)
			printf ("buff[%d] = %d\n", i, buff[i]);
	}
	return NULL;
}

int main (int argc, char *argv[])
{
	int i, nthreads, count[MAXNTHREADS];
	pthread_t tid_produce[MAXNTHREADS], tid_consume;


	if (argc != 3)
		wp_critical ("usage: %s <#items> <#theads>", argv[0]);
	nitems = WP_MIN (atoi(argv[1]), MAXNITEMS);
	nthreads = WP_MIN (atoi (argv[2]), MAXNTHREADS);

	for (i = 0; i < nthreads; i++)
	{
		count[i] = 0;
		wp_pthread_create (&tid_produce[i], NULL, produce, &count[i]);
	}
	wp_pthread_create (&tid_consume, NULL, consume, NULL);

	for (i = 0;  i < nthreads; i++)
	{
		wp_pthread_join (tid_produce[i], NULL);
		printf ("count[%d] = %d\n", i, count[i]);
	}
	wp_pthread_join (tid_consume, NULL);
	wp_message ("pthread_cond_signal() executed %d times\n", nsignal);
	
	return 0;
}
