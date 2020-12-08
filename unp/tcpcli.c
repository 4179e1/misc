#include "unp.h"

int main (int argc, char* argv[]) {
	int sockfd;
	struct sockaddr_in servaddr;

	if (argc != 2) {
		err_quit ("usage: tcpcli <IPaddress>");
	}

	sockfd = Socket (AF_INET, SOCK_STREAM, 0);

	memset (&servaddr, 0, sizeof (servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons (SERV_PORT);
	Inet_pton (AF_INET, argv[1], &servaddr.sin_addr);

	Connect (sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	str_cli (stdin, sockfd);

	{
		struct linger ling;
		ling.l_onoff = 1;
		ling.l_linger = 0;

		Setsockopt (sockfd, SOL_SOCKET, SO_LINGER, (void *)&ling, sizeof (ling));
	}

	exit(0);
}
