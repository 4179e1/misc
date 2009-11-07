#include <stdio.h>
#include "array_sort.h"

/**
 * @brief Selection Sort for array.
 *
 * select the minium card from the unsorted cards in right hand,
 * insert it into the end of the sorted cards in left hand.
 *
 * @note Complexity: O(n^2).
 * @parma array The array need to be sort.
 * @parma len Length of array.
 * @return The sorted array.
 */
int *selection_sort (int *array, int len)
{
	int i, j; 
	int *min;
	
	/* Not necessary to check the last element */
	for (i = 0; i < len - 1; i++)
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

	return array;
}
