#if 0
gcc -g -Wall -o `basename $0 .c` $0 -lpthread
exit 0
#endif
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread_func (void *arg) {
	pause();
	return ((void *)0);
}

int main (int argc, char *argv[])
{
	int i, n;
	pthread_t tid;
	for (i = 0; i < 1024; i++){
		n = pthread_create (&tid, NULL, thread_func, NULL);
		if (n != 0) {
			printf ("error creating thread #%d\n", i);
			break;
		}
		else {
			printf ("thread #%d created\n", i);
		}
	}
	pause ();
	return 0;

}
