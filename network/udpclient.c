#include <stdlib.h>
#include <libwp.h>

#define MAXLINE 1024

void dg_cli (FILE *fp, int sockfd, const struct sockaddr *servaddr, socklen_t servlen)
{
	int n;
	char sendline[MAXLINE], recvline[MAXLINE + 1];

	while (wp_fgets (sendline, MAXLINE, fp) != NULL)
	{
		wp_sendto (sockfd, sendline, strlen (sendline), 0, servaddr, servlen);
		n = wp_recvfrom (sockfd, recvline, MAXLINE, 0, NULL, NULL);
		recvline[n] = 0;
		wp_fputs (recvline, stdout);
	}
}

int main (int argc, char *argv[])
{
	int sockfd;
	struct sockaddr_in servaddr;

	if (argc != 2)
	{
		wp_critical ("usage: %s <IPaddress>", argv[0]);
	}

	memset (&servaddr, 0, sizeof (servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons (2345);
	wp_inet_pton (AF_INET, argv[1], &servaddr.sin_addr);

	sockfd = wp_socket (AF_INET, SOCK_DGRAM, 0);
	dg_cli (stdin, sockfd, (struct sockaddr *)&servaddr, sizeof (servaddr));

	exit (0);
}
