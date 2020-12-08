#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

char hex_char[] = "0123456789abcdef";

char *h2x (char *buf, unsigned long value)
{
	int shift = 0;
	unsigned long copy = value;
	char *org = buf;

	while (copy) {
		copy >>= 4;
		shift++;
	}
	if (shift == 0)
	{
		shift++;
	}
	if (shift & 0x01)
	{
		shift++;
	}

	/* print shift */

	shift <<= 2;
	while (shift > 0) {
		shift -= 4;
		*(buf++) = hex_char[(value >> shift) & 0x0F];
	}

	*buf = '\0';

	return org;
}

int main (int argc, char *argv[])
{
	char buf[1024] = {0};

	assert (argc == 2);

	unsigned long i = atoi (argv[1]);

	printf ("%s\n", h2x(buf, i));

	return 0;
}
