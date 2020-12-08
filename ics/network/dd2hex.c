#if 0
clang -Wall -o `basename $0 .c` $0
exit 0
#endif
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main (int argc, char *argv[])
{
	struct in_addr address;

	if (argc != 2)
	{
		fprintf (stderr, "usage %s dd\n", argv[0]);
		return -1;
	}

	inet_pton (AF_INET, argv[1], &(address.s_addr));

	printf ("%#x\n", ntohl (address.s_addr));
}

