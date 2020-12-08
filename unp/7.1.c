#include "unp.h"

int main (void) {
	int sockfd;
	int rcvbuf_size, sndbuf_size;
	socklen_t len;

	sockfd = Socket (AF_INET, SOCK_STREAM, 0);

	len = sizeof(rcvbuf_size);

	getsockopt (sockfd, SOL_SOCKET, SO_RCVBUF, (void *)&rcvbuf_size, &len);
	getsockopt (sockfd, SOL_SOCKET, SO_SNDBUF, (void *)&sndbuf_size, &len);

	printf ("TCP SO_RCVBUF = %d, SO_SNDBUF = %d\n", rcvbuf_size, sndbuf_size);

	return 0;
}
