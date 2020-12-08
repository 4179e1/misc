#include <stdio.h>

#define MULTI_HASH_FACTOR 0.6180339887

int multi_hash (int key, int size)
{
	double d;

	d = (double)key;
	printf ("%f\n", d);
	
	d *= MULTI_HASH_FACTOR;
	printf ("%f\n", d);
	
	d -= (int)d;
	printf ("%f\n", d);
	
	return (int)(size * d);
}

int main (void)
{
	printf ("%d\n", multi_hash (123456, 16384));
	return 0;
}
