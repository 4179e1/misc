#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "calc.h"

#define MAXLINE 100

int li;
char line[MAXLINE];

int getop( char s[] )
{
	int i, c, tmp;
	
	if( line[li] == '\0' )
		if( getline(line, MAXLINE ) == 0 )
			return EOF;
		else
			li = 0;

	while( ( s[0] = c = line[li++]) == ' ' || c == '\t' )
		;
	s[1] = '\0';
	i = 0;

	if( c == '-' )
	{
		if( isdigit( c = line[li++] ) || c == '.' )
			s[++i] = c;
		else
		{
			li --;
			return '-';
		}
	}

	if( islower( c ) )
	{
		tmp = c;
		while( islower( s[++i] = c = line[li++]) )
			;
		s[i] = '\0';
		li--;

		if( strlen( s ) > 1 )
			return NAME;
		else
			return tmp;
	}

	if( !isdigit( c ) && c != '.') 
		return c;

	if( isdigit( c ) )
		while( isdigit( s[++i] = c = line[li++]) )
			;
	if( c == '.' )
		while( isdigit( s[++i] = c = line[li++]) )
			;
	s[i] = '\0';
	li--;
	return NUMBER;
}

