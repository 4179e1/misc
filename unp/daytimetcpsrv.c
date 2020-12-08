#include <stdio.h>
#include <stdlib.h>
#include "unp.h"
#include <time.h>

#include "debug_macro.h"

int main(int argc, char* argv[]) {
	int listenfd, connfd;
	socklen_t len;
	struct sockaddr_in servaddr, cliaddr;
	char buff[MAXLINE];
	time_t ticks;

	listenfd = Socket (AF_INET, SOCK_STREAM, 0);

	memset (&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl (INADDR_ANY);
	servaddr.sin_port = htons(9999);

	Bind (listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	Listen (listenfd, LISTENQ);

	for (;;) {
		len = sizeof(cliaddr);
		connfd = Accept (listenfd, (struct sockaddr*) &cliaddr, &len);
		printf ("Connection from %s, port %d\n",
				Inet_ntop (AF_INET, &cliaddr.sin_addr, buff, sizeof(buff)), ntohs (cliaddr.sin_port));
		ticks = time(NULL);
		snprintf (buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		{
			int i = strlen(buff);
			char *c = &buff[0];
			while ( i > 0 ) {
				Write (connfd, c, 1);
				c++;
				i--;
			}
		}
		Shutdown (connfd, SHUT_RDWR);
		Close (connfd);
	}
}
