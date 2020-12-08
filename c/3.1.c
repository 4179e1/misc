#include<stdio.h>

int binsearch(int x, char v[],int n)
{
	int low, high, mid;
	
	low = 0;
	high = n - 1;

	while( low <= high )
	{
		mid = ( low + high ) / 2;
		printf("low:%d\thigh:%d\tmid:%d\n",low,high,mid);
		if ( x < v[mid] )
			high = mid - 1;
		else if ( x > v[mid] )
			low = mid + 1;
		else return mid;
	}

	return -1;
}

main()
{
	int x = 1;
	int n = 5;
	char v[n];

	int i;
	for ( i = 0; i < n; i++ )
		v[i] = i + 1;
	printf( "%d in v[%d]\n",x,binsearch ( x,v,n ) );

	return 0;
}
