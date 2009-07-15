#include <stdio.h>

main()
{
	double sum, v;

	sum = 0;
	while( scanf("%lf", &v) == 1 )
		printf("\t%.2f", sum += v);

	return 0;
}
