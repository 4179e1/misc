#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "calc.h"

int getop( char s[] )
{
	int i, c, tmp;

	while( ( s[0] = c = getch() ) == ' ' || c == '\t' )
		;
	s[1] = '\0';
	i = 0;

	if( c == '-' )
	{
		if( isdigit( c = getch() ) || c == '.' )
			s[++i] = c;
		else
		{
			if( c != EOF )
				ungetch(c);
			return '-';
		}
	}

	if( islower( c ) )
	{
		tmp = c;
		while( islower( s[++i] = c = getch()) )
			;
		s[i] = '\0';
		if( c != EOF )
			ungetch( c );

		if( strlen( s ) > 1 )
		{
			printf("getop.c/s[]:%s\n",s);
			return NAME;
		}
		else
		{
			printf("getop.c/c = %c", c);
			return tmp;
		}
	}

	if( !isdigit( c ) && c != '.') 
		return c;

	if( isdigit( c ) )
		while( isdigit( s[++i] = c = getch()) )
			;
	if( c == '.' )
		while( isdigit( s[++i] = c = getch()) )
			;
	s[i] = '\0';
	if( c != EOF )
		ungetch( c );
	return NUMBER;
}

