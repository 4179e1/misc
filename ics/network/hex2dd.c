#if 0
gcc -Wall -o `basename $0 .c` $0
exit 0
#endif
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main (int argc, char *argv[])
{
	struct in_addr address;
	unsigned int addr;
	char present[INET_ADDRSTRLEN];

	if (argc != 2)
	{
		fprintf (stderr, "usage %s hex\n", argv[0]);
		return -1;
	}

	sscanf (argv[1], "%x", &addr);
	address.s_addr = htonl (addr);

	inet_ntop (AF_INET, &address, present, sizeof (present));

	printf ("%s\n", present);
}


