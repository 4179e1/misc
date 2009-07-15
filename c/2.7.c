#include <stdio.h>

main()
{
	int j;
	int i = srand(2);
	for ( j = 0; j <= 5; ++j )
		 printf("%d\n",rand(i));
}
