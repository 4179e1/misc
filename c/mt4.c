#include <stdio.h>

main()
{
	int i;
	double s[3] = {1.0, 2.0, 3.0};
	printf("aa:%s\n",s);
	for ( i = 0; s[i] != '\0'; i++ )
		printf("%f\t", s[i]);
	return 0;
}
