#include <stdio.h>
#define N 7
//#define int S[] {4,3,7,5,2,6,1}

void prints(int gap, int i, int j, int s[] )
{
	int ix;
	printf("gap = %d\ti = %d\tj = %d\tj+gap=%d\n",gap,i,j,j+gap);
	for (ix = 0; ix < N; ix++)
		printf("%4d",ix);
	printf("\n");
	for (ix = 0; ix < N; ix++)
		printf("%4d",s[ix]);
	printf("\n\n");
}

void shellsort(int s[], int n)
{
	int gap, i, j, temp;
	printf("n=%d\n",n);

	for (gap = n/2; gap > 0; gap /=2)
	{
		printf("gap=%d\n",gap);
		for ( i = gap; i < n; i++ )
		{
			printf("i=%d\n",i);
			for ( j = i - gap; j >= 0 && s[j] > s[j+gap]; j -= gap )
			{
				prints(gap,i,j,s);
				temp = s[j];
				s[j] = s[j+gap];
				s[j+gap] = temp;
			}
			printf("gap = %d\ti = %d\tj = %d\tj+gap=%d\n",gap,i,j,j+gap);
		}
	}
}

main()
{
	int s[] = {6,3,7,5,2,4,1};
	shellsort(s,N);
	return 0;
}
