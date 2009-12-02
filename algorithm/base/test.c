#include <stdio.h>
#include "base.h"

int main (void)
{
	random_init();

	int i;
	for (i = 0; i < 10; i++)
	{
		printf ("%d\n", random (1, 6));
	}

	dice (4, 6);

	return 0;
}
