#include <stdlib.h>
#include <libwp.h>

#define MAXLINE 1024

void dg_cli (FILE *fp, int sockfd, const struct sockaddr *servaddr, socklen_t servlen)
{
	int n;
	char sendline[MAXLINE], recvline[MAXLINE + 1];
	socklen_t len;
	struct sockaddr_in *reply_addr;
	char address[INET_ADDRSTRLEN];
	

	reply_addr = wp_malloc (servlen);

	while (wp_fgets (sendline, MAXLINE, fp) != NULL)
	{
		wp_sendto (sockfd, sendline, strlen (sendline), 0, servaddr, servlen);
		len = servlen;
		n = wp_recvfrom (sockfd, recvline, MAXLINE, 0, (struct sockaddr *)reply_addr, &len);
		if (len != servlen || memcmp (servaddr, reply_addr, len) != 0)
		{
			wp_debug ("reply from %s (ignored)", wp_inet_ntop (AF_INET, &(reply_addr->sin_addr), address, sizeof (address)));
			continue;
		}
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
