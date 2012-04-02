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
 * @param array The array need to be sort.
 * @param len Length of array.
 * @return The sorted array, Ascending.
 */
int *insert_sort (int *array, int len)
{
	/**
	 * j for the select card in array
	 * i for the boundary of the sorted group in the beginging 
	 * i + 1 for the index for the selected card after iteration.
	 * key for the value of the selected card.
	*/
	
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
