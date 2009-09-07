#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/tcp.h>

#include "unp.h"

#define DEBUG
#include "debug_macro.h"

int main(int argc, char* argv[]) {
	int sockfd, n, rcvbuf, mss;
	socklen_t len, optlen;
	char recvline[MAXLINE + 1];
	struct sockaddr_in servaddr, cliaddr;

	if (argc != 2) {
		err_quit ("USAGE: a.out <IPaddress>");
	}

	sockfd = Socket (AF_INET, SOCK_STREAM, 0);

	memset (&servaddr, 0, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(9999);

	Inet_pton (AF_INET, argv[1], &servaddr.sin_addr);

	{
		optlen = sizeof (rcvbuf);
		Getsockopt (sockfd, SOL_SOCKET, SO_RCVBUF, (void *)&rcvbuf, &len);
		optlen = sizeof (mss);
		Getsockopt (sockfd, IPPROTO_TCP, TCP_MAXSEG, (void *)&mss, &len);
		printf ("Before connect, SO_RCVBUf = %d, TCP_MAXSEG = %d\n", rcvbuf, mss);
	}

	Connect (sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	{
		optlen = sizeof (rcvbuf);
		Getsockopt (sockfd, SOL_SOCKET, SO_RCVBUF, (void *)&rcvbuf, &len);
		optlen = sizeof (mss);
		Getsockopt (sockfd, IPPROTO_TCP, TCP_MAXSEG, (void *)&mss, &len);
		printf ("After connect, SO_RCVBUf = %d, TCP_MAXSEG = %d\n", rcvbuf, mss);
	}

	len = sizeof(cliaddr);
	Getsockname (sockfd, (struct sockaddr*) &cliaddr, &len);

	printf ("local addr: %s, port: %d\n", inet_ntop (AF_INET, (struct sockaddr*)&cliaddr.sin_addr, recvline, len), cliaddr.sin_port);

	{
		int count = 0;
		while ((n = Read(sockfd, recvline, MAXLINE)) > 0) {
			count++;
			recvline[n] = 0;
			if (fputs (recvline, stdout) == EOF) {
				err_sys ("fputs error");
			}
		}
		printf ("Read count = %d\n", count);
	}

	if (n < 0) {
		err_sys ("read error");
	}

	exit(0);
}
