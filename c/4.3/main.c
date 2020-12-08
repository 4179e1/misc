#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

#define MAXOP 100

int main()
{
	int type;
	double op2;
	char s[MAXOP];
	
	double a, b;

	while( ( type = getop( s ) ) != EOF )
	{
		switch ( type )
		{
			case NUMBER:
				push( atof( s ) );
				break;
			case '+':
				a = pop();
				b = pop();
				push( a + b );
				break;
			case '-':
				op2 = pop();
				push( pop() - op2 );
				break;
			case '*':
				push( pop() * pop() );
				break;
			case '/':
				op2 = pop();
				if ( op2 != 0.0 )
					push( pop() / op2 );
				else
					printf("error: zero divisor\n");
				break;
			case '\n':
				printf("output:\t%f\n", pop() );
				break;
			default:
				printf("error: unknown command %s\n", s );
				break;
		}
	}
	return 0;
}
