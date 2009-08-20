#include "unp.h"

void
str_echo (int sockfd) {
	ssize_t n;
	char buf[MAXLINE];

again:
	while ((n = Read(sockfd, buf, MAXLINE)) > 0) {
		Writen (sockfd, buf, n);
	}
	if (n < 0 && errno == EINTR) {
		goto again;
	} else if (n < 0) {
		err_sys ("str_echo: read error");
	}
}

void
str_cli (FILE* fp, int sockfd) {
	char sendline[MAXLINE], recvline[MAXLINE];
	while (Fgets (sendline, MAXLINE, fp) != NULL) {
		Writen (sockfd, sendline, strlen(sendline));
		if (Readline (sockfd, recvline, MAXLINE) == 0) {
			err_quit ("str_cli: server terminated prematurely");
		}

		Fputs (recvline, stdout);
	}
}
