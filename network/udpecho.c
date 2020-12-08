#include <libwp.h>

void dg_echo (int sockfd, struct sockaddr *cliaddr, socklen_t clilen)
{
	int n;
	socklen_t len;
	char mesg[1024];

	while (1)
	{
		len = clilen;
		n = wp_recvfrom (sockfd, mesg, sizeof (mesg), 0, cliaddr, &len);
		wp_sendto (sockfd, mesg, n, 0, cliaddr, len);
	}
}

int main (int argc, char *argv[])
{
	int 	sockfd;
	struct sockaddr_in servaddr, cliaddr;

	sockfd = wp_socket (AF_INET, SOCK_DGRAM, 0);
	memset (&servaddr, 0, sizeof (servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl (INADDR_ANY);
	servaddr.sin_port = htons (2345);

	wp_bind (sockfd, (struct sockaddr *)&servaddr, sizeof (servaddr));
	dg_echo (sockfd, (struct sockaddr *)&servaddr, sizeof (cliaddr));

	return 0;
}
