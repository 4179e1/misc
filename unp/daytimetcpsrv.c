#include <stdio.h>
#include <stdlib.h>
#include "unp.h"
#include <time.h>

#include "debug_macro.h"

int main(int argc, char* argv[]) {
	int listenfd, connfd;
	struct sockaddr_in servaddr;
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
		connfd = Accept (listenfd, (struct sockaddr*) NULL, NULL);
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
		Close (connfd);
	}
}
