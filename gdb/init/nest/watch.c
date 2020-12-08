#if 0
gcc -Wall -g -o `basename $0 .c` $0
exit
#endif

#include <stdio.h>

int i = 0;

int main (void)
{
	int i = 3;

	printf ("i = %d\n", i);

	i = 5;

	printf ("i = %d\n", i);

	return 0;
}
