#include <stdio.h>
#include "array_sort.h"

/**
 * @def The maxium number for integer
 */
#define MERGE_SORT_SENTINEL 0x7fffffff

/** 
 * @brief Merge two sorted sub-squence
 *
 * @param array The input array
 * @param p 
 * @param q
 * @param r
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
	
	la [n1] = MERGE_SORT_SENTINEL;
	ra [n2] = MERGE_SORT_SENTINEL;

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
