#include "unp.h"

void
dg_cli (FILE *fp, int sockfd, const struct sockaddr *servaddr, socklen_t servlen)
{
	int n;
	char sendline[MAXLINE], recvline[MAXLINE + 1];
	socklen_t len;
	struct sockaddr *preply_addr;

	preply_addr = Malloc (servlen);

	while (Fgets (sendline, MAXLINE, fp) != NULL)
	{
		Sendto (sockfd, sendline, strlen(sendline), 0, servaddr, servlen);
		len = servlen;
		n = Recvfrom (sockfd, recvline, MAXLINE, 0, preply_addr, &len);
		if (len != servlen || memcmp (servaddr, preply_addr, len) != 0)
		{
			printf ("reply form %s (ignored)\n", Sock_ntop (preply_addr, len));
			continue;
		}
		Fputs (recvline, stdout);
	}
	free (preply_addr);
}

int main (int argc, char *argv[])
{
	int sockfd;
	struct sockaddr_in servaddr;

	if (argc != 2)
		err_quit ("usage: udpcli <IPaddress>");

	memset (&servaddr, 0, sizeof (servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons (SERV_PORT);
	Inet_pton (AF_INET, argv[1], &servaddr.sin_addr);

	sockfd = Socket (AF_INET, SOCK_DGRAM, 0);

	dg_cli (stdin, sockfd, (struct sockaddr *)&servaddr, sizeof (servaddr));

	exit (0);
}
