#include "util.h"
#include <wppthread.h>

pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;
pthread_t tid1, tid2;

void *thread1 (void *arg)
{
	wp_pthread_rwlock_rdlock (&rwlock);
	printf("thread1() got a read lock\n");
	sleep (3);
	pthread_cancel (tid2);
	sleep (3);
	wp_pthread_rwlock_unlock (&rwlock);
	return NULL;
}

void *thread2 (void *arg)
{
	printf ("thread2() trying to obtain a write lock\n");
	wp_pthread_rwlock_rdlock (&rwlock);
	printf ("thread2() got a write lock\n");
	sleep (1);
	wp_pthread_rwlock_unlock (&rwlock);
	return NULL;
}

int main (int argc, char *argv[])
{
	void *status;

	wp_pthread_create (&tid1, NULL, thread1, NULL);
	sleep (1);
	wp_pthread_create (&tid2, NULL, thread2, NULL);

	wp_pthread_join (tid2, &status);
	if (status != PTHREAD_CANCELED)
		wp_warning ("thread2 status = %p\n", status);
	wp_pthread_join (tid1, &status);
	if (status != NULL)
		wp_warning ("thread1 status = %p\n", status);

	return 0;
}

