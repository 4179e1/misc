#include <stdio.h>
#include <ctype.h>

int getword( char *word, int lim )
{
	int c, getch(void);
	void ungetch(int);

	char *w = word;

	while ( isspace(c =getch()))
		;

/* 
	  "*w++ = c;"
equals:
	  {*w = c;
	  w++;}
*/
	if ( c!= EOF )
		*w++ = c;

	if( !isalpha(c) && c != '_' )
	{
		*w = '\0';
		return c;
	}

	for( ; --lim > 0; w++)
		if( !isalnum( *w = getch()) && *w != '_')
		{
			ungetch(*w);
			break;
		}
	
	*w = '\0';

	return word[0];
}

