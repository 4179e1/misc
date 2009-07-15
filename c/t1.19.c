#include <stdio.h>
#define MAXLINE 1000
#define LONGLINE 20

void reverse( char s[] );

int getline ( char s[], int lim )
{
	int c, i;
	
	printf ( "insert a new line : " );
	for ( i = 0; i < lim - 1 && ( c = getchar() ) != EOF && c != '\n'; ++i )
		s[i] = c;
	if ( c == '\n' )
	{
		s[i] = c;
		++i;
	}
	s[i] = '\0';
//	printf ("i in getline : %d\n", i );
	return i;
}

main()
{
	char line[MAXLINE];

	while( getline( line, MAXLINE ) > 0 )
	{
		reverse( line );
		printf ( "after reverse : %s", line );
	}

	return 0;
}

void reverse( char s[] )
{
	int i,j;
	char temp;

	i = 0;

	while ( s[i] != '\0' )
		++i;
	--i;
	
	if ( s[i] == '\n' )
		--i;

	j = 0;
	while ( j < i )
	{
		temp = s[i];
		s[i] = s[j];
		s[j] = temp;
		--i;
		++j;
	}
}
