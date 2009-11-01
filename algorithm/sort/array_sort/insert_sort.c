#include <stdio.h>
#include "array_sort.h"

int *insert_sort (int *array, int len)
{
	int i, j, key;

	for (j = 1; j < len; j++)
	{
		key = array[j];
		i = j - 1;

		while (i >= 0 && array[i] > key)
		{
			array[i + 1] = array[i];
			i--;
		}
		array[i + 1] = key;
	}

	return array;
}
