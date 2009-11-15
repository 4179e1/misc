#include <stdio.h>
#include "array_sort.h"

/**
 * @brief Bubble Sort for array.
 *
 * Repeatedly swapping adjacent elements that are out of order.
 *
 * @note Complexity: O(n^2).
 * @param array The array need to be sort.
 * @param len Length of array.
 * @return The sorted array.
 */
int *bubble_sort (int *array, int len)
{
	int i, j;
	for (i = 0; i < len; i++)
	{
		for (j = i + 1; j < len; j++)
		{
			if (array[i] > array[j])
			{
				swap (&array[i], &array[j]);
			}
		}
	}

	return array;
}
