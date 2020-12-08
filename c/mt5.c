#include <stdio.h>
#define MAXVAL 100

int sp = 0;
int ix;
double val[MAXVAL];

void push( double f )
{
	if( sp < MAXVAL )
	{
		val[sp++] = f;
		printf("stack.c/push()/line12/val[]:\n");
		for( ix = 0; ix < sp; ix++ )
			printf("%f\t",val[ix]);
		putchar('\n');
	}
	else
		printf("error: stack full, can't push %g\n",f );
//	printf("stack.c/push()/line16/val[]:%s",val);
}

double pop( void )
{
		printf("stack.c/pop()/line25/val[]:\n");
		for( ix = 0; ix < sp; ix++ )
			printf("%f\t",val[ix]);
		putchar('\n');

	if ( sp > 0 )
		return val[--sp];
	else
	{
		printf("error: stack empty\n");
		return 0.0;
	}
}

main()
{
	push( 3.0 );
	push( 4.0 );
	push( pop() + pop() );
	printf("out:%f\n",pop() );
	return 0;
}
