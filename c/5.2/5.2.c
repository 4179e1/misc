#include <stdio.h>
#include <ctype.h>
#define SIZE	1
int getch(void);
int ungetch(int);

main()
{
	int i, n, array[SIZE], getint(int *);

	for( n = 0; n < SIZE && getint(&array[n]) != EOF; n++ )
		;
	for( i = 0; i < SIZE ; i++)
		printf("%d",array[i]);
}



int getint(int *pn)
{
	int c, sign;
	while ( isspace( c = getch() ) )
			;
	if( !isdigit(c) && c != EOF && c !=	'+' && c != '-' )
	{
		ungetch(c);
		return 0;
	}	
	sign = ( c == '-' ? -1 : 1 );
	if ( c == '+' || c == '-' )
		c = getch();
	for ( *pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + ( c - '0' );
	*pn *= sign;
	if( c != EOF );
	return c;
}
