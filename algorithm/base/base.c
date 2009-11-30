#include <stdio.h>
#include "base.h"

void swap (int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void print_array (int *array, int len)
{
	int i;
	for (i = 0; i < len; i++)
	{
		printf (" %d", array[i]);
	}

	printf ("\tEOA\n");
}
