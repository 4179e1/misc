#include<stdio.h>

int brace, brack, paren;
int nml = 1;
void in_comment( void );
void in_quote( int c );
void search( int c );

main()
{
	int c, d;
	extern int brace, brack, paren;
	brace = brack = paren = 0;
	extern nml;

	while( ( c = getchar() ) != EOF )
	{
		if ( c == '\n' )
			++nml;
		else if ( c == '/' )
		{
			if ( ( c = getchar() ) == '*' )
				in_comment();
			else if ( c == '\n' )
				++nml;
			else search( c );
		}
		else if ( c == '\'' || c == '"' )
			in_quote( c );
		else
			search( c );

		if ( brace < 0 )
		{
			printf("Unbalance barces at line %d.\n", nml);
			brace = 0;
		}
		else if ( brack < 0 )
		{
			printf("Unbalance brackeks at line %d.\n", nml);
			brack = 0;
		}
		else if ( paren < 0 )
		{
			printf("Unbalance parentheses at line %d.\n", nml);
			paren = 0;
		}
	}
	
	if ( brace > 0 )
		printf("Unbalance barces.\n");
	if ( brack > 0 )
		printf("Unbalance brackets.\n");
	if ( paren > 0 )
		printf("Unbalance parentheses.\n");
}

void search( int c )
{
	extern brace, brack, paren;
	if ( c == '{' )
		++brace;
	else if ( c == '}' )
		--brace;
	else if ( c == '[' )
		++brack;
	else if ( c == ']' )
		--brack;
	else if ( c == '(' )
		++paren;
	else if ( c == ')' )
		--paren;
}

void in_comment()
{
	int c, d;
	
	c = getchar();
	if( c == '\n' )
		++nml;
	d = getchar();

	while ( c != '*' || d != '/' )
	{
		if ( d == '\n' )
			++nml;
		c = d;
		d = getchar();
	}

	if ( d == '\n' )
		++nml;
}

void in_quote( int c )
{
	extern int nml;
	int d, e;
	
	while ( ( d = getchar() ) != c )
	{
		if ( d == '\n' )
			++nml;
		else if ( d == '\\' )
		{
			e = getchar();
			if( e == '\n' )
				++nml;
		}
	}
}
	
