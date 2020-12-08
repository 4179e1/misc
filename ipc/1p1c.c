#include "util.h"
#include <semaphore.h>
#include <wppthread.h>

#define NBUFF 10
#define SEM_MUTEX "/mutex_1p1c"
#define SEM_NEMPTY "/nempty_1p1c"
#define SEM_NSTORED "/nstored_1p1c"

int nitems;		/* read-only by producer and consumer */
struct {
	int buff[NBUFF];
	sem_t *mutex, *nempty, *nstored;
} shared;


void *produce (void *arg)
{
	int i;

	for (i = 0; i < nitems; i++)
	{
		wp_sem_wait (shared.nempty);
		wp_sem_wait (shared.mutex);
		shared.buff [i % NBUFF] = i;
		wp_sem_post (shared.mutex);
		wp_sem_post (shared.nstored);
	}
	
	return NULL;
}


void *consume (void *arg)
{
	int i;	
	for (i = 0; i < nitems; i++)
	{
		wp_sem_wait (shared.nstored);
		wp_sem_wait (shared.mutex);
		if (shared.buff [i % NBUFF] != i)
			wp_message ("buff[%d] = %d\n", i, shared.buff[i % NBUFF]);
		wp_sem_post (shared.mutex);
		wp_sem_post (shared.nempty);
	}
	return NULL;
}

int main (int argc, char *argv[])
{
	pthread_t tid_produce, tid_consume;

	if (argc != 2)
		wp_critical ("usage: %s <#items>", argv[0]);
	nitems = atoi (argv[1]);

	wp_set_exit_level (WP_LOG_WARNING);
	shared.mutex = wp_sem_open (SEM_MUTEX, O_CREAT | O_EXCL, FILE_MODE, 1);
	shared.nempty = wp_sem_open (SEM_NEMPTY, O_CREAT | O_EXCL, FILE_MODE, NBUFF);
	shared.nstored = wp_sem_open (SEM_NSTORED, O_CREAT | O_EXCL, FILE_MODE, 0);

	wp_pthread_create (&tid_produce, NULL, produce, NULL);
	wp_pthread_create (&tid_consume, NULL, consume, NULL);

	wp_pthread_join (tid_produce, NULL);
	wp_pthread_join (tid_consume, NULL);

	wp_sem_unlink (SEM_MUTEX);
	wp_sem_unlink (SEM_NEMPTY);
	wp_sem_unlink (SEM_NSTORED);

	exit (0);
}
