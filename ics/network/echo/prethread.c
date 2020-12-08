#include <libwp.h>
#include <stdlib.h>
#include <wppthread.h>

#define NTHREADS 4
#define SBUFSIZE 16

typedef struct
{
	int *buf;		/* buffer array */
	int n;			/* maximum number of slots */
	int front;		/* buf[(front + 1)%n] is first item */
	int rear;		/* buf[read%n] is last item */
	sem_t mutex;	/* protects accesss to buf */
	sem_t slots;	/* counts available slots */
	sem_t items;	/* counts available items */
} sbuf_t;

void sbuf_init (sbuf_t *sp, int n)
{
	sp->buf = wp_calloc (n, sizeof (int));
	sp->n = n;
	sp->front = sp->rear = 0;
	wp_sem_init (&sp->mutex, 0, 1);
	wp_sem_init (&sp->slots, 0, n);
	wp_sem_init (&sp->items, 0, 0);
}

void sbuf_insert (sbuf_t *sp, int item)
{
	P(&sp->slots);
	P(&sp->mutex);
	sp->buf[(++sp->rear)%(sp->n)] = item;
	V(&sp->mutex);
	V(&sp->items);
}

int sbuf_remove (sbuf_t *sp)
{
	int item;
	P(&sp->items);
	P(&sp->mutex);
	item = sp->buf[(++sp->front)%(sp->n)];
	V(&sp->mutex);
	V(&sp->slots);
	return item;
}

void sbuf_free (sbuf_t *sp)
{
	wp_sem_destroy (&sp->mutex);
	wp_sem_destroy (&sp->slots);
	wp_sem_destroy (&sp->items);
	free (sp->buf);
}

static sbuf_t sbuf;
static int byte_cnt;
static sem_t mutex;

static void init_echo_cnt (void)
{
	wp_sem_init (&mutex, 0, 1);
	byte_cnt = 0;
}

void echo_cnt (int connfd)
{
	int n;
	char buf[1024];
	wp_rio_t *rio;
	static pthread_once_t once = PTHREAD_ONCE_INIT;

	wp_pthread_once (&once, init_echo_cnt);

	rio = wp_rio_new (connfd);
	while ((n = wp_rio_readlineb (rio, buf, sizeof (buf))) != 0)
	{
		P(&mutex);
		byte_cnt += n;
		printf ("thread %d received %d (%d total) bytes on fd %d\n", (int)pthread_self(), n, byte_cnt, connfd);
		V(&mutex);
		wp_rio_writen (rio, buf, n);
	}

	wp_rio_free (rio);
}

void *thread (void *vargp)
{
	wp_pthread_detach (pthread_self());
	while (1)
	{
		int connfd = sbuf_remove (&sbuf);
		echo_cnt (connfd);
		wp_close (connfd);
	}
}

int main (int argc, char *argv[])
{
	int i, listenfd, connfd, port;
	socklen_t clientlen = sizeof (struct sockaddr_in);
	struct sockaddr_in clientaddr;
	pthread_t tid;

	if (argc != 2)
	{
		wp_critical ("usage: %s <port>\n", argv[0]);
	}

	port = atoi (argv[1]);
	sbuf_init (&sbuf, SBUFSIZE);
	listenfd = wp_open_listenfd (port);
	if (listenfd < 0)
	{
		wp_critical ("error");
	}

	for (i = 0; i < NTHREADS; i++)
	{
		wp_pthread_create (&tid, NULL, thread, NULL);
	}


	while (1)
	{
		connfd = wp_accept (listenfd, (struct sockaddr *)&clientaddr, &clientlen);
		sbuf_insert (&sbuf, connfd);
	}
}
