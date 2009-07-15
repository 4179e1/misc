#include <stdio.h>

main( int argc, int *argv[])
{
	int i;

	for ( i = 0; i < argc; i++ )
		printf("%s%s", argv[i], ( i < argc - 1 ? " " : "" ));

	printf("\n");

	return 0;
}
