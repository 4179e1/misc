#include <stdio.h>

void swap(int a, int b)
{
	int tmp = a;
	a = b;
	b = tmp;
}


int main(void)
{
	int a = 1;
	int b = 2;

	printf ("before swap: a = %d, b = %d\n", a, b);
	swap (a, b);
	printf ("after swap: a = %d, b = %d\n", a, b);

	return 0;
}
