#include "array_sort.h"
#include "base.h"

/**
 * @brief counting sort
 *
 * @note Complexity O ( n );
 * @param a the input array;
 * @param b the sorted output array, only len_b elements will be written
 * @param len_a length of array a;
 * @param len_b length of array b;
 * @param k all elements in array a should be lesser than or equal to k;
 * @return the sorted array, that is array b;
 */
int *counting_sort (int *a, int *b, int len_a, int len_b, int k)
{
	int i, j;
	/* there are (k + 1) elements between 0 and k */
	int c[k + 1];
	for (i = 0; i <= k; i++)
	{
		c[i] = 0;
	}

	/* c[i]: contains number of element i */
	for (j = 0; j < len_a; j++)
	{
		c[a[j]]++;
	}

	/* c[i]: contians numbers than lesser than or equal to element i */
	for (i = 1; i <= k; i++)
	{
		c[i] += c[i-1];
	}

	for (j = len_a - 1, i = 0; (i < len_b) && (j >= 0); j--, i++)
	{
		/**
		 * j: 			index of array i, range (0, len_a - 1);
		 * a[j]:		In array a, what's in index j?
		 * c[ a[j] ]:	how many elements are lesser than or equal to a[j]?
		 * c[a[j]] - 1:	In array b, where's the position for a[j]?
		 * b[c[a[j]] - 1] = a[j]:	place a[j] to the right position on array b.
		 */
		b[c[a[j]] - 1] = a[j];
		/* we have add a[j] to array b, reduce counting by 1 */
		(c[a[j]])--;
	}

	return b;
}
