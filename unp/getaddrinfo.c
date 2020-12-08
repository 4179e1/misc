#if 0
clang -Wall -g -o `basename $0 .c` $0 `pkg-config --cflags --libs glib-2.0`
exit 0
#endif
#include <stdio.h>
#include <assert.h>
#include <netdb.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main (int argc, char *argv[])
{
	struct addrinfo hints, *res;
	char address[INET_ADDRSTRLEN];

	assert (argc >= 2);

	memset (&hints, 0, sizeof hints);
	hints.ai_flags = AI_CANONNAME;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	assert (getaddrinfo (argv[1], argv[2], &hints, &res) == 0);

	struct addrinfo *ptr;
	struct sockaddr_in *addr;

	for (ptr = res; ptr != NULL; ptr = ptr->ai_next)
	{
		printf ("ADDRLEN: %jd CANONNAME: %s\n",(intmax_t)(ptr->ai_addrlen), ptr->ai_canonname);
		addr = (struct sockaddr_in *)(ptr->ai_addr);
		assert (inet_ntop (ptr->ai_family, (void *)&(addr->sin_addr), address, sizeof(address)) != NULL);
		printf ("ADDRESS: %s PORT: %d\n", address, htons (addr->sin_port));
	}
	freeaddrinfo (res);

	return 0;
}
