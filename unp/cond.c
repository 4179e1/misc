#if 0
${CC=clang} -o `basename $0 .c` -Wall $0 `pkg-config --libs --cflags libwp0 wppthread0`
exit 0
#endif
#include <libwp.h>
#include <wpmacros.h>
#include <wppthread.h>
#include <stdlib.h>
#define MAXNITEMS 1000000
#define MAXNTHREADS 100

int nitems;
int buff[MAXNITEMS];

struct {
	pthread_mutex_t mutex;
	int nput;		/* next index to store */
	int nval;		/* next value to store */
} put = {
	.mutex = PTHREAD_MUTEX_INITIALIZER
};

struct {
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	int nready; /* number ready for consumer */
} nready = 
{
	.mutex = PTHREAD_MUTEX_INITIALIZER,
	.cond = PTHREAD_COND_INITIALIZER
};

void *produce  (void *arg)
{
	while (1)
	{
		wp_pthread_mutex_lock (&put.mutex);
		if (put.nput >= nitems)
		{
			wp_pthread_mutex_unlock (&put.mutex);
			wp_message ("producer[%jd] done!", pthread_self());
			return (NULL);
		}
		buff[put.nput] = put.nval;
		put.nput++;
		put.nval++;
		wp_pthread_mutex_unlock (&put.mutex);

		wp_pthread_mutex_lock (&nready.mutex);
		if (nready.nready == 0)
		{
			pthread_cond_signal (&nready.cond);
		}
		nready.nready++;
		wp_pthread_mutex_unlock (&nready.mutex);
		*((int *) arg) += 1;
	}

}

void *consume  (void *arg)
{
	int i;

	for (i = 0; i < nitems; i++)
	{
		wp_pthread_mutex_lock (&nready.mutex);
		while (nready.nready == 0)
		{
			wp_pthread_cond_wait (&nready.cond, &nready.mutex);
		}
		nready.nready--;
		wp_pthread_mutex_unlock (&nready.mutex);

		if (buff[i] != i)
		{
			wp_warning ("buff[%d] = %d\n", i, buff[i]);
		}

	}
	wp_message ("consumer done!");
	return NULL;
}

int main (int argc, char *argv[])
{
	int i, nthreads, count[MAXNTHREADS];
	pthread_t tid_produce[MAXNTHREADS], tid_consume;

	if (argc != 3)
	{
		wp_critical ("usage: %s <#items> <#theads>", argv[0]);
	}
	nitems = WP_MIN(atoi(argv[1]), MAXNITEMS);
	nthreads = WP_MIN(atoi (argv[2]), MAXNTHREADS);

	for (i = 0; i < nthreads; i++)
	{
		count[i] = 0;
		wp_pthread_create (&tid_produce[i], NULL, produce, &count[i]);
	}

	wp_pthread_create (&tid_consume, NULL, consume, NULL);

	for (i = 0; i < nthreads; i++)
	{
		wp_pthread_join (tid_produce[i], NULL);
		printf ("count[%d] = %d\n", i, count[i]);
	}
	wp_pthread_join (tid_consume, NULL);

	return 0;
}
