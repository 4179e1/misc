#include <stdio.h>
#include <limits.h>
#include "array_sort.h"

/**
 * @def The maxium number for integer
 */
#define MERGE_SORT_SENTINEL 0x7fffffff

/** 
 * @brief Merge two sorted sub-sequences
 *
 * @param array The input array
 * @param p Beginning index number of array.
 * @param q	Middle index number of array, end of the first sub-sequence.
 * @param r Endding index number of array.
 * @note Attention: p <= q < r
 */
static void merge (int *array, int p, int q, int r)
{
	int n1 = q - p + 1;
	int n2 = r - q;
	int i, j, k;

	/* alloc extra 1 slot for sentinel */
	int la[n1 + 1];
	int ra[n2 + 1];

	for (i = 0; i < n1; i++)
	{
		la[i] = array[p + i];
	}

	for (j = 0; j < n2; j++)
	{
		ra[j] = array [q + j + 1];
	}
	
	la [n1] = INT_MAX;
	ra [n2] = INT_MAX;

	i = 0;
	j = 0;

	for (k = p; k <= r; k++)
	{
		/* even a integer equal to sentiel still works */
		if (la[i] <= ra[j])
		{
			array[k] = la[i];
			i++;
		}
		else
		{
			array[k] = ra[j];
			j++;
		}
	}
}

/**
 * @brief Merge sort for array
 *
 * Divide: Divede the n-element sequence to be sorted into two subsequences
 * of n/2 elements each.
 * Conquer: Sort the two subsequences recursively using merge sort.
 * Combine: Merger the two sorted subsequences to produce the sorted answer.
 *
 * @note Complexity O( n*lg(n) )
 * @param array The array need to be sort
 * @param p Beginning index number of array
 * @param r Ending index number of array
 * @return The sorted array.
 */

int *merge_sort (int *array, int p, int r)
{
	if (p < r)
	{
		int q = (p + r) / 2;
		merge_sort (array, p, q);
		merge_sort (array, q + 1, r);
		merge (array, p, q, r);
	}

	return array;
}
