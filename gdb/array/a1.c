#if 0
gcc -Wall -g -o `basename $0 .c` $0
exit
#endif

#include <stdio.h>
#include <stdlib.h>

int *x;

int main ()
{
	x = (int *)malloc (25 * sizeof (int));
	x[3] = 12;

	return 0;
}
