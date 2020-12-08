#include "unp.h"

#ifndef OPEN_MAX
#define OPEN_MAX 1024
#endif /* OPEN_MAX */

int
main (int argc, char *argv[]) {
	int i, maxi, listenfd, connfd, sockfd;
	int nready;
	ssize_t n;
	char buf[MAXLINE];
	socklen_t clilen;
	struct pollfd client[OPEN_MAX];
	struct sockaddr_in cliaddr, servaddr;

	listenfd = Socket (AF_INET, SOCK_STREAM, 0);

	memset (&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;

	servaddr.sin_addr.s_addr = htonl (INADDR_ANY);
#if 0
	/* only 192.168.1.95 is accepted, 127.0.0.1 won't be accepted */
	Inet_pton (AF_INET, "192.168.1.95", &servaddr.sin_addr);
#endif

	servaddr.sin_port = htons (SERV_PORT);

	Bind (listenfd, (struct sockaddr *)&servaddr, sizeof (servaddr));

	Listen (listenfd, LISTENQ);

	client[0].fd = listenfd;
	client[0].events = POLLIN;
	for (i = 1; i < OPEN_MAX; i++) 
	{
		client[i].fd = -1;
	}
	maxi = 0;

	for (;;) {
		nready = Poll (client, maxi + 1, -1);
		if (client[0].revents & POLLIN) 
		{
			clilen = sizeof(cliaddr);
			connfd = Accept (listenfd, (struct sockaddr *)&cliaddr, &clilen);

			for (i = 1; i < OPEN_MAX; i++) 
			{
				if (client[i].fd < 0) 
				{
					client[i].fd = connfd;
					break;
				}
			}

			if (i == OPEN_MAX) 
			{
				err_quit ("too many clients");
			}

			client[i].events = POLLIN;

			if (i > maxi) 
			{
				maxi = i;
			}

			if (nready-- <= 0) 
			{
				continue;
			}
		}

		for (i = 1; i <= maxi; i++) 
		{
			if ((sockfd = client[i].fd) < 0) 
			{
				continue;
			}

			if (client[i].revents & (POLLIN | POLLERR)) 
			{
				if ((n = read(sockfd, buf, MAXLINE)) < 0) 
				{
					if (errno == ECONNRESET) 
					{
						Close (sockfd);
						client[i].fd = -1;
					}
					else 
					{
						err_sys ("read error");
					}
				}
				else if (n == 0) 
				{
					Close (sockfd);
					client[i].fd = -1;
				} 
				else 
				{
					Writen (sockfd, buf, n);
				}

				if (--nready <= 0) 
				{
					break;
				}
			}
		}
	}
}
