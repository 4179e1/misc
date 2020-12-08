#include <stdio.h>
#include <errno.h>

int main (void)
{
	fprintf (stderr, "ERRNO STDERR %d\n", errno);
	printf ("ERRNO %d\n", errno);
	fprintf (stderr, "ERRNO STDERR %d\n", errno);
	printf ("ERRNO %d\n", errno);
	return 0;
}
