#include <stdio.h>

void rcomment( int c );
void in_comment( void );
void echo_quote( int c );

main()
{
	int c;

	while ( ( c = getchar() ) != EOF )
		rcomment( c );
	return 0;
}

void rcomment( int c )
{
	int d,e;

	if ( c == '/' )
		if ( ( d = getchar() ) == '*' )
			in_comment();
		else if ( d == '/' )
		{
			while( (e = getchar()) != '\n' )
			{
			}
			putchar ( e ); 
		}
		else
		{
			putchar( c );
			putchar( d );
		}
	else if ( c =='\'' || c == '"' )	//c为单引号或双引号
		echo_quote( c );
	else
		putchar( c );
}

void in_comment( void )
{
	int c, d;

	c = getchar();	/*prev character*/
	d = getchar();	/*curr character*/
	while ( c != '*' || d != '/' )
	{
		c = d;
		d = getchar();
	}
}

void echo_quote( int c )
{
	int d;
	putchar( c );

	while ( ( d = getchar() ) != c )
	{
		putchar( d );	
		if ( d == '\\' )	/*如果遇到转义序列\,显示\后面的字符*/
			putchar( getchar() );
	}
	putchar(d);
}
