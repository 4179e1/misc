#include "unp.h"
#define NODEBUG
#include "debug_macro.h"

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

#if 0
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
#endif

#if 0
void
str_cli (FILE *fp, int sockfd) {
	int maxfdp1;
	fd_set rset;
	char sendline[MAXLINE], recvline[MAXLINE];

	FD_ZERO(&rset);
	for (;;) {
		FD_SET (fileno(fp), &rset);
		FD_SET (sockfd, &rset);
		maxfdp1 = MAX (fileno(fp), sockfd) + 1;

		Select (maxfdp1, &rset, NULL, NULL, NULL);

		if (FD_ISSET (sockfd, &rset)) {
			if (Readline (sockfd, recvline, MAXLINE) == 0) {
				err_quit ("str_cli: server terminated prematurely");
			}
			Fputs (recvline, stdout);
		}

		if (FD_ISSET (fileno(fp), &rset)) {
			if (Fgets (sendline, MAXLINE, fp) == NULL) {
				return;
			}
			Writen (sockfd, sendline, strlen(sendline));
		}
	}
}
#endif

void
str_cli (FILE *fp, int sockfd) {
	int maxfdp1, stdineof;
	fd_set rset;
	char buf[MAXLINE];
	int n;

	stdineof = 0;
	FD_ZERO (&rset);

	for (;;) {
		if (stdineof == 0) {
			FD_SET (fileno (fp), &rset);
		}
		FD_SET (sockfd, &rset);
		maxfdp1 = MAX (fileno (fp), sockfd) + 1;
		Select (maxfdp1, &rset, NULL, NULL, NULL);

		if (FD_ISSET(sockfd, &rset)) {
			if ((n = Read (sockfd, buf, MAXLINE)) == 0) {
				if (stdineof == 1) {
					return;
				} else {
					err_quit ("str_cli: server terminated permaturely");
				}
			}
			Write (fileno(stdout), buf, n);
			DEBUG_PRINT;
		}

		if (FD_ISSET (fileno(fp), &rset)) {
			if ((n = Read(fileno(fp), buf, MAXLINE)) == 0) {
				stdineof = 1;
				Shutdown (sockfd, SHUT_WR);
				FD_CLR (fileno(fp), &rset);
				continue;
			}

			Writen (sockfd, buf, n);
			DEBUG_PRINT;
		}
	}
}
