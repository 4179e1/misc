#include <stdio.h>
extern int m1_max (int a, int b);
extern int m2_max (int a, int b);

int main (void)
{
	int a = 1;
	int b = 2;
	printf ("%d\n", m1_max (a, b));
	printf ("%d\n", m2_max (a, b));
	printf ("%d\n", m3_max (a, b));

	return 0;
}
