#include <stdio.h>

#define IN 1
#define OUT 0

main()
{
	int c, state;	//state 表示当前字符的前一个字符在单词中的位置

	state = OUT;

	while ( ( c = getchar() ) != EOF )
	{
		if ( c == ' ' || c == '\n' || c == '\t' )
		{
			if ( state == IN )
			{
				putchar ( '\n' );
				state = OUT;
			}
		}
		else if ( state == OUT )
		{
			putchar ( c );
			state = IN;
		}
		else
			putchar ( c );
	}
}
