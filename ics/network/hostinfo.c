#if 0
clang -Wall -o `basename $0 .c` $0
exit 0
#endif

#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <assert.h>

int main (int argc, char *argv[])
{
	char **pp;
	struct in_addr addr;
	struct hostent *hostp;

	if (argc != 2)
	{
		fprintf (stderr, "usage: %s <domain name or dotted-decimal\n", argv[0]);
		return -1;
	}

	if (inet_pton (AF_INET, argv[1], &addr) == 1)
	{
		hostp = gethostbyaddr ((const char *)&addr, sizeof (addr), AF_INET);
	}
	else
	{
		hostp = gethostbyname (argv[1]);
	}
	assert (hostp != NULL);

	printf ("offical hostname: %s\n", hostp->h_name);

	for (pp = hostp->h_aliases; *pp != NULL; pp++)
	{
		printf ("alias: %s\n", *pp);
	}

	for (pp = hostp->h_addr_list; *pp != NULL; pp++)
	{
		addr.s_addr = *((unsigned int *)*pp);
		printf ("address: %s\n", inet_ntoa (addr));
	}

	return 0;
}
