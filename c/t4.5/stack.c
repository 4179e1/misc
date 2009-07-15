#include <stdio.h>
#include "calc.h"

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push( double f )
{
	if( sp < MAXVAL )
	{
		val[sp++] = f;
	}
	else
		printf("error: stack full, can't push %g\n",f );
}

double pop( void )
{
	int ix;
	printf("stack:");
	for( ix = 0; ix < sp; ix++ )
		printf("\t%g", val[ix] );
	putchar('\n');

	if ( sp > 0 )
		return val[--sp];
	else
	{
		printf("error: stack empty\n");
		return 0.0;
	}
}

void clear( void )
{
	sp = 0;
}
