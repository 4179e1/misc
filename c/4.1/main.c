#include <stdio.h>
#define MAXLINE 1000
//#include "getline.c"
//#include "strindex.c"

int getline( char line[], int max );
int strindex( char source[], char searchfor[] );

char pattern[] = "ould";

main()
{
	char line[MAXLINE];
	int found = 0;
	
	while ( getline( line, MAXLINE ) > 0 )
		if ( strindex( line, pattern ) >= 0 )
		{
			printf( "%s", line );
			found++;
		}
	return found;
}
