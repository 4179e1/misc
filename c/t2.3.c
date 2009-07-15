#include <stdio.h>
#define YES 1
#define NO 0

int htoi(char s[])
{
	int hexdigit, i, inhex, n;

	i = 0;
	if ( s[i] == '0' )
	{
		++i;
		if ( s[i] == 'x' || s[i] == 'X' )
			++i;
	}

	n = 0;
	inhex = YES;
	for ( ; inhex == YES; ++i )
	{
		if ( s[i] >= '0' && s[i] <= '9' )
			hexdigit = s[i] - '0';
		else if ( s[i] >= 'a' && s[i] <= 'f' )
			hexdigit = s[i] - 'a' + 10;
		else if ( s[i] >= 'A' && s[i] <= 'F' )
			hexdigit = s[i] - 'A' + 10;
		else
			inhex = NO;

		if ( inhex == YES )
		{
			n = 16*n + hexdigit;
//			printf("%d\n",n);
		}
	}
	return n;
}

main()
{
	printf("%d\n",htoi("0x32"));
	return 0;
}
