#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP 100
#define NUMBER '0'

#define BUFSIZE 100

#define MAXVAL 100

int sp = 0;
int ix;
double val[MAXVAL];

char buf[BUFSIZE];
int bufp = 0;

int getch( void );
void ungetch( int );

int getop( char [] );
void push( double );
double pop ( void );

main()
{
	int type;
	double op2;
	double tmp;
	char s[MAXOP];
	
	double a, b;

	while( ( type = getop( s ) ) != EOF )
	{
		switch ( type )
		{
			case NUMBER:
//				tmp = atof( s );
//				printf("main.c/main()/line18/tmp:%f\n",tmp);
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

int getop( char s[] )
{
	int i, c;

	while( ( s[0] = c = getch() ) == ' ' || c == '\t' )
		;
	s[1] = '\0';
	if( !isdigit( c ) && c != '.' )
		return c;
	i = 0;
	if( isdigit( c ) )
		while( isdigit( s[++i] = c = getch()) )
			printf("getop.c/getop()/line19/s[]:%s\n",s);
	if( c == '.' )
		while( isdigit( s[++i] = c = getch()) )
			printf("getop.c/getop()/line22/s[]:%s\n",s);
	s[i] = '\0';
	printf("getop.c/getop()/line24/s[]:%s\n",s);
	if( c != EOF )
		ungetch( c );
	return NUMBER;
}

int getch( void )
{
	return ( bufp > 0 ) ? buf[--bufp] : getchar();
}

void ungetch( int c )
{
	if ( bufp >= BUFSIZE )
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
	printf("get_stack.c/ungetch/line18:%s\n",buf);
}

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

