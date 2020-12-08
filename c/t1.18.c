#include <stdio.h>
#define MAXLINE 1000
#define LONGLINE 20

int rm( char s[] );

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
	printf ("i in getline : %d\n", i );
	return i;
}

main()
{
	char line[MAXLINE];

	while( getline( line, MAXLINE ) > 0 )
	{
		if ( rm( line ) > 0 )
			printf("%s",line);
	}

	return 0;
}

int rm( char s[] )
{
	int i;

	i = 0;

	while ( s[i] != '\n' )
		++i;
	--i;

	while ( i >= 0 && ( s[i] == ' ' || s[i] == '\t' ) )
		--i;

	if ( i >= 0 )
	{
		++i;
		s[i] = '\n';
		++i;
		s[i] = '\0';
	}

	printf( "i in rm : %d\n", i );
	
	return i;
}
