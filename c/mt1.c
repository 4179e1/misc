#include <stdio.h>

main()
{
	char c;
	while ( ( c = getchar() ) != EOF )
		if ( c != '\n' )
			printf("%d\n", c );
	return 0;
}
