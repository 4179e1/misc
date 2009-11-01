#include <stdio.h>
#include "array_sort.h"

static void swap (int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

int *selection_sort (int *array, int len)
{
	int i, j; 
	int *min;
	
	for (i = 0; i < len; i++)
	{
		min = &array[i];
		for(j = i; (j < len); j++)
		{
			if (array[j] < *min)
			{
				min = &array[j];
			}
		}
		swap (&array[i], min);
	}
}
