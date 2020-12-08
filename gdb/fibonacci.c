#if 0
gcc -Wall -g -o `basename $0 .c` $0
exit
#endif
#include <stdio.h>

int fibonacci (n)
{
	if (n <= 0 || n == 1)
	{
		return 1;
	}

	return fibonacci (n - 1) + fibonacci (n - 2);
}

int main (void)
{
	printf ("fibonacci(4) is %d.\n", fibonacci(3));

	return 0;
}
