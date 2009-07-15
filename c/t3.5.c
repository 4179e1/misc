#include <stdio.h>
#include <string.h>
#define abs(x) ( (x) < 0 ? -(x) : (x) )

void reverse( char s[] )
{
	int i, j, c;
	for ( i = 0, j = strlen( s ) - 1;  i < j; i++, j-- )
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

void itob( int n, char s[], int b )
{
	int i, j, sign;

	sign = n;
	i = 0;
	do {
		j = abs( n % b );
		s[i++] = ( j <= 9 ) ? j + '0' : j + 'a' - 10;
	} while ( ( n /= b ) != 0 );
	if ( sign < 0 )
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

void prints( char s[] )
{
	int i;
	for( i = 0; s[i] != '\0'; i++)
		printf("%c", s[i]);
	putchar('\n');
}

main()
{
	int n = 1234;
	int b = 16;
	char s[100];
	itob( n, s, b );
	prints( s );
	return 0;
}

