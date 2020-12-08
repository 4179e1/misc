#include <stdlib.h>
#include <libwp.h>

typedef struct
{
	int maxfd;
	fd_set read_set;
	fd_set ready_set;
	int nready;
	int maxi;
	int clientfd[FD_SETSIZE];
	wp_rio_t *clientrio[FD_SETSIZE];
} pool;

static int byte_cnt = 0;

void init_pool (int listenfd, pool *p)
{
	int i;
	p->maxi = -1;
	for (i = 0; i < FD_SETSIZE; i++)
	{
		p->clientfd[i] = -1;
	}

	p->maxfd = listenfd;
	FD_ZERO (&p->read_set);
	FD_SET (listenfd, &p->read_set);
}

void add_client (int connfd, pool *p)
{
	int i;
	p->nready--;
	for (i = 0; i < FD_SETSIZE; i++)
	{
		/* find an available slot */
		if (p->clientfd[i] < 0)
		{
			p->clientfd[i] = connfd;
			p->clientrio[i] = wp_rio_new (connfd);
			
			FD_SET (connfd, &p->read_set);

			if(connfd > p->maxfd)
			{
				p->maxfd = connfd;
			}

			if (i > p->maxi)
			{
				p->maxi = i;
			}
			break;
		}
	}
	if (i == FD_SETSIZE)
	{
		wp_critical ("%s error: too many clients", __func__);
	}
}

void check_clients (pool *p)
{
	int i, connfd, n;
	char buf[1024];
	wp_rio_t *rio;

	for (i = 0; (i <= p->maxi) && (p->nready > 0); i++)
	{
		connfd = p->clientfd[i];
		rio = p->clientrio[i];

		if ((connfd > 0) && (FD_ISSET (connfd, &p->ready_set)))
		{
			p->nready--;
			if ((n = wp_rio_readlineb (rio, buf, sizeof (buf))) != 0)
			{
				byte_cnt += n;
				printf ("Server received %d (%d total) bytes on fd %d\n", n, byte_cnt, connfd);
				wp_rio_writen (rio, buf, n);
			}
			else /* EOF */
			{
				wp_close (connfd);
				FD_CLR (connfd, &p->read_set);
				p->clientfd[i] = -1;
				wp_rio_free (p->clientrio[i]);
			}
		}
	}
}

int main (int argc, char *argv[])
{
	int listenfd, connfd, port;
	socklen_t clientlen = sizeof (struct sockaddr_in);
	struct sockaddr_in clientaddr;
	static pool pool;

	if (argc != 2)
	{
		wp_critical ("usage: %s <port>\n", argv[0]);
	}

	port = atoi (argv[1]);

	listenfd = wp_open_listenfd (port);
	if (listenfd < 0)
	{
		wp_critical ("failed");
	}

	init_pool (listenfd, &pool);

	while (1)
	{
		pool.ready_set = pool.read_set;
		pool.nready = wp_select (pool.maxfd + 1, &pool.ready_set, NULL, NULL, NULL);

		if (FD_ISSET (listenfd, &pool.ready_set))
		{
			connfd = wp_accept (listenfd, (struct sockaddr *)&clientaddr, &clientlen);
			add_client (connfd, &pool);
		}

		check_clients (&pool);
	}
	return 0;
}
