#include "unp.h"

void
sig_chld (int signo) {
	pid_t pid;
	int stat;

	while ( (pid = waitpid (-1, &stat, WNOHANG)) > 0) {
		printf ("child %d terminated\n", pid);
	}
	return;
}

int main(int argc, char* argv[]) {
	int listenfd, connfd;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;

	listenfd = Socket (AF_INET, SOCK_STREAM, 0);

	memset (&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl (INADDR_ANY);
	servaddr.sin_port = htons (SERV_PORT);

	Bind (listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	Listen (listenfd, LISTENQ);

	Signal (SIGCHLD, sig_chld);

	for (;;) {
		clilen = sizeof(cliaddr);
		if ((connfd = accept (listenfd, (struct sockaddr*)&cliaddr, &clilen)) < 0) {
			if (errno == EINTR) {
				continue;
			} else {
				err_sys ("accept error");
			}
		}

		if ((childpid = fork()) == 0) {
			Close (listenfd);
			str_echo (connfd);
			sleep (10);
			Close (connfd);
			exit(0);
		}

		Close(connfd);
	}
}


