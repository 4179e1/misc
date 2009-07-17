#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define DEBUG
#include "debug_macro.h"

#define MAXLINE 1024


int main(int argc, char* argv[]) {
	int sockfd, n;
	char recvline[MAXLINE + 1];
	struct sockaddr_in servaddr;

	if (argc != 2) {
		printf ("USAGE: a.out <IPaddress>\n");
		exit (1);
	}

	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf ("socket error\n");
		exit (2);
	}

	memset (&servaddr, 0, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13);

	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
		printf ("inet_pton error for %s\n", argv[1]);
		exit (3);
	}

	if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
		printf ("connect error\n");
		exit (4);
	}

	while ((n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0;
		if (fputs (recvline, stdout) == EOF) {
			printf ("fputs error\n");
			exit(5);
		}
	}

	if (n < 0) {
		printf ("read error");
		exit(6);
	}

	exit(0);
}
