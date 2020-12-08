#if 0
gcc -g -Wall -o `basename $0 .c` $0 -lpthread
exit 0
#endif
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int count;

void *thread_func (void *arg) {
	pause();
	return ((void *)0);
}

int main (int argc, char *argv[])
{
	int i, n;
	pthread_t tid;
	count = 0;
	for (i = 0; i < 1024; i++){
		n = pthread_create (&tid, NULL, thread_func, (void*)&count);
		if (n != 0) {
			printf ("error creating thread #%d\n", i);
			break;
		}
		else {
			printf ("thread #%d created\n", i);
		}
		pthread_detach (tid);
	}
	pause ();
	return 0;

}
