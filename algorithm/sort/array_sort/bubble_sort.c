#include <stdio.h>
#include "array_sort.h"
#include "base.h"

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
	/* array[0, i) for the sorted sequence */
	int i, j;
	for (i = 0; i < len; i++)
	{
		for (j = len - 1; j > i; j--)
		{
			if (array[j] < array[j - 1])
			{
				swap (&array[j], &array[j - 1]);
			}
		}
	}

	return array;
}
