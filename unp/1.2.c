#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "unp.h"

#define DEBUG
#include "debug_macro.h"


int main(int argc, char* argv[]) {
	int sockfd, n;
	char recvline[MAXLINE + 1];
	struct sockaddr_in servaddr;

	if (argc != 2) {
		err_quit ("USAGE: a.out <IPaddress>");
	}

	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		err_sys ("socket error");
	}

	memset (&servaddr, 0, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13);

	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
		err_quit ("inet_pton error for %s", argv[1]);
	}

	if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
		err_sys ("connect error");
	}

	while ((n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0;
		if (fputs (recvline, stdout) == EOF) {
			err_sys ("fputs error");
		}
	}

	if (n < 0) {
		err_sys ("read error");
	}

	exit(0);
}
