#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "calc.h"

#define MAXOP 100

main()
{
	int type;
	int i;
	int var = 0;
	double op1, op2;
	double v = 0.0;
	char s[MAXOP];
	double variable[26];
	
	for( i = 0; i < 26; i++ )
		variable[i] = 0.0;

	while( ( type = getop( s ) ) != EOF )
	{
		switch ( type )
		{
			case NUMBER:
				push( atof( s ) );
				break;
			case NAME:
				mathfnc( s );
				break;
			case '+':
				push( pop() + pop() );
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
			case '%':
				op2 = pop();
				if( op2 != 0.0 )
					push( fmod(pop(), op2) );
				else
					printf("error: zero divisor\n");
				break;
			case '?':
				op2 = pop();
				printf("stack_top:\t%.8g\n",op2);
				push( op2 );
				break;
			case 'c':
				clear();
				break;
			case 'd':
				op2 = pop();
				push( op2 );
				push( op2 );
				break;
			case 's':
				op1 = pop();
				op2 = pop();
				push( op1 );
				push( op2 );
				break;
			case '=':
				pop();
				if( isupper( var ) )
				{
					variable[var - 'A'] = pop();
					printf("variable[%c] = %f\n", var, variable[var - 'A']);
				}
				else
					printf("error: no variable name\n");
				break;
			case '\n':
				v = pop();
				printf("output:\t%f\n", v );
				break;
			default:
				if ( isupper( type ) )
					push(variable[type - 'A']);
				else if ( type == 'v' )
					push( v );
				else
					printf("error: unknown command %s\n", s );
				break;
		}
		var = type;
	}
	return 0;
}
