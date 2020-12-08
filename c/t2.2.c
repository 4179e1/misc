#include <stdio.h>
#define LIM 9

main()
{
	enum loop {NO, YES};
	enum loop reloop = YES;
	int s[LIM];
	char c;
	int i = 0;
	while ( reloop == YES )
		if ( i >= LIM - 1)
			reloop = NO;
		else if ( (c = getchar()) == '\n' )
		{
			s[i] = '\n';
			reloop = NO;
		}
		else if ( c == EOF )
			reloop = NO;
		else
		{
			s[i] = c;
			++i;
		}
	
	int j = 0;
	for ( j = 0; j <= i; j++ )
		printf ("%c\t",s[j]);
	printf ("\n");
}
