#include "unp.h"

int 
main (int argc, char *argv[]) {
	int i, maxi, maxfd, listenfd, connfd, sockfd;
	int nready, client[FD_SETSIZE];
	ssize_t n;
	fd_set rset, allset;
	char buf[MAXLINE];
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;
	
	listenfd = Socket (AF_INET, SOCK_STREAM, 0);
	memset (&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl (INADDR_ANY);
	servaddr.sin_port = htons (SERV_PORT);
	Bind (listenfd, (struct sockaddr*) &servaddr, sizeof(servaddr));
	Listen (listenfd, LISTENQ);

	maxfd = listenfd;
	maxi = -i; /* index for client[] */
	for (i = 0; i < FD_SETSIZE; i++) {
		client[i] = -1;
	}
	FD_ZERO (&allset);
	FD_SET (listenfd, &allset);

	for (;;) {
		rset = allset;
		nready = Select (maxfd + 1, &rset, NULL, NULL, NULL);

		if (FD_ISSET (listenfd, &rset)) {
			clilen = sizeof(cliaddr);
			connfd = Accept (listenfd, (struct sockaddr*)&cliaddr, &clilen); /* what if one more conn to accept ? */

			for (i = 0; i < FD_SETSIZE; i++) {
				if (client[i] < 0) {
					client[i] = connfd;
					break;
				}
			}

			if (i == FD_SETSIZE) {
				err_quit ("too many clients");
			}

			FD_SET (connfd, &allset);
			if (connfd > maxfd) {
				maxfd = connfd;
			}

			if (i > maxi) {
				maxi = i;
			}

			if (--nready <= 0) {
				continue;
			}
		}

		for (i = 0; i <= maxi; i++) {
			if ((sockfd = client[i]) < 0) {
				continue;
			}

			if (FD_ISSET (sockfd, &rset)) {
				if ((n = Read (sockfd, buf, MAXLINE)) == 0) {
					Close (sockfd);
					FD_CLR (sockfd, &allset);
					client[i] = -1;
				} else {
					Writen (sockfd, buf, n);
				}

				if (--nready <= 0) {
					break;
				}

			}
		}
	}
}

