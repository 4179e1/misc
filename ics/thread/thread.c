#if 0
gcc -Wall -o `basename $0 .c` $0 -lwpbase -lwppthread -lpthread
exit
#endif
#include <libwp.h>

#define N 2

void *thread (void *vargp);

char **ptr;

int main ()
{
	int i;
	pthread_t tid;
	char *msgs[N] = 
	{
		"Hello from foo",
		"Hello from bar"
	};

	ptr = msgs;
	for (i = 0; i < N; i++)
	{
		wp_pthread_create (&tid, NULL, thread, (void *)i);
	}

	pthread_exit (NULL);
}

void *thread (void *vargp)
{
	int myid = (int)vargp;
	static int cnt = 0;
	printf ("[%d]: %s (cnt=%d)\n", myid, ptr[myid], ++cnt);
}
