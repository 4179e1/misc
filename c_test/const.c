#include <stdio.h>

int main (void)
{
	int i = 8;
	int b = 9;

	const int *ci = &i; /* same as int const * */
	int const *ci2 = &i;

	int *const ic = &i;

	{
		ci = &b;
		printf ("*ci = %d\n", *ci);
#if 0
		*ci = 8; /* error: assignment of read-only location ‘*ci’ */
#endif
	}

	{
		ci2 = &b;
#if 0
		*ci2 = b; /* assignment of read-only location ‘*ci2’ */
#endif
	}

	{
#if 0
		ic = &b; /*  error: assignment of read-only variable ‘ic’ */
#endif
		*ic = b;
		printf ("*ic = %d\n", *ic);
	}

	return 0;
}
