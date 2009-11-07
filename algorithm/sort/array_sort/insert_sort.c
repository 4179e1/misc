#include <stdio.h>
#include "array_sort.h"

/**
 * @brief Insert Sort for array.
 *
 * Get a new card from unsorted group on right hand.
 * Insert it into the sorted group in left hand,
 * Cards on left hand that greater than the new card are right shift by 1,
 * the new card goes in the empty slot after right shift.
 *
 * @note Complexity: O(n^2).
 * @parma array The array need to be sort.
 * @parma len Length of array.
 * @return The sorted array, Ascending.
 */
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
