#include <stdlib.h>
#include <stdbool.h>
#define HAVE_SYS_EPOLL_H
#include <libwp.h>
#include <errno.h>
#include <sys/epoll.h>

#define MAX_EVENTS 10

#define MAXLINE 1024


static char buf[MAXLINE];

/*
 * @return true to remove descriptor
 *         false to keep it
 */
bool echo(int connfd) 
{
	ssize_t n;

	wp_debug ("echo begin %d\n", __LINE__);
	while (1)
	{
		n = wp_read (connfd, buf, sizeof (buf));
		if (n == -1)
		{
			if (errno == EAGAIN)
			{
				wp_debug ("read later");
				break;
			}
			wp_critical ("read error");
		}
		else if (n == 0)
		{
			wp_debug ("nothing to read, close");
			return true;
		}

		wp_debug ("read %d bytes\n", n);
		wp_write (connfd, buf, n);
	}
	wp_debug ("echo end %d\n", __LINE__);
	return false;
}

bool setnonblocking (int fd)
{
	int opts;
	opts = wp_fcntl (fd, F_GETFL, 0);
	if (opts < 0)
	{
		return false;
	}

	opts = opts | O_NONBLOCK;
	if (wp_fcntl (fd, F_SETFL, opts) < 0)
	{
		return false;
	}

	return true;
}

int main (int argc, char *argv[])
{
	int listenfd, connfd, port;
	struct sockaddr_in clientaddr;
	socklen_t clientlen = sizeof (struct sockaddr_in);
	struct epoll_event ev, events[MAX_EVENTS];
	int epfd, nfds, n, fd;
	int i = 1;

	if (argc != 2)
	{
		wp_critical ("usage: %s <port>", argv[0]);
	}

	port = atoi (argv[1]);
	listenfd = wp_open_listenfd (port);
	if (listenfd < 0)
	{
		wp_critical ("open_listenfd failed");
	}

	epfd = wp_epoll_create (MAX_EVENTS);
	if (epfd == -1)
	{
		wp_critical ("epoll_create failed");
	}

	ev.events = EPOLLIN;
	ev.data.fd = listenfd;
	if (wp_epoll_ctl (epfd, EPOLL_CTL_ADD, listenfd, &ev) == -1)
	{
		wp_critical ("epoll_ctl failed");
	}

	while (1)
	{
		wp_debug ("loop %d before epoll_wait", i++);
		nfds = epoll_wait (epfd, events, MAX_EVENTS, -1);
		if (nfds == -1)
		{
			wp_critical ("epoll_wait failed");
		}
		wp_debug ("epoll_wait return", i++);

		for (n = 0; n < nfds; ++n)
		{
			if (events[n].data.fd == listenfd)
			{
				wp_debug ("a new connection");
				connfd = wp_accept (listenfd, (struct sockaddr *)&clientaddr, &clientlen);
				if (connfd == -1)
				{
					wp_critical ("accept failed");
				}

				if (!setnonblocking (connfd))
				{
					wp_critical ("unbale to set fd nonblock");
				}

				ev.events = EPOLLIN | EPOLLET;
				ev.data.fd = connfd;
				if (wp_epoll_ctl (epfd, EPOLL_CTL_ADD, connfd, &ev) == -1)
				{
					wp_critical ("epoll_ctl failed");
				}
			}
			else if (events[n].events & EPOLLIN)
			{
				if (echo (events[n].data.fd))
				{
					fd = events[n].data.fd;
					wp_epoll_ctl (epfd, EPOLL_CTL_DEL, fd, NULL);
					wp_close (fd);
				}
			}
		}
	}
}
