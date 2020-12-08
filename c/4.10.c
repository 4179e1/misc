#include <stdio.h>

void printd(int n)
{
	if ( n < 0 )
	{
		putchar('-');
		n = -n;
	}

	printf("Debug: n = %d\n", n );

	if ( n / 10 )
		printd( n / 10 );
	putchar( n % 10 + '0' );
}

main()
{
	printd( 1234 );
	return 0;
}
