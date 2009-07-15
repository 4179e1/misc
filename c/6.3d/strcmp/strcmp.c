#include <stdio.h>

main()
{	
	char c[] = "a_b";
	printf("%d\n",strcmp("a_b",c));
	printf("%d\n",strcmp("ab",c));
	printf("%d\n",strcmp("ab",c));
	return 0;
}
