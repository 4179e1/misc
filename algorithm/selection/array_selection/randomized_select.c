#include <assert.h>
#include "array_selection.h"
#include "base.h"

/* 
 * @brief randomized select
 *
 * @note Complexity O (n).
 * @param i the ith smallest number in array, 0 < i <= r + 1.
 * @return the ith smallest number in array.
 */
int randomized_select (int *array, int p, int r, int i)
{
	int q;
	int k;

	assert (0 < i <= r + 1);

	if (p == r)
	{
		return array[p];
	}

	q = randomized_partition (array, p, r);
	k = q - p + 1;
	if (i == k)
	{
		return array[q];
	}
	else if (i < k)
	{
		return randomized_select (array, p, q - 1, i);
	}
	else	/* if (i > k) */
	{
		return randomized_select (array, q + 1, r, i - k);
	}
}

int randomized_select_loop (int *array, int p, int r, int i)
{
	int q;
	int k;
	int begin, end;

	assert (0 < i <= r + 1);
	begin = p;
	end = r;
	while(1)
	{
		q = randomized_partition (array, begin, end);
		k = q - p + 1;
		if (i == k)
		{
			return array[q];
		}
		else if (i < k)
		{
			end = q - 1;
		}
		else
		{
			begin = q + 1;
			i -= k;
		}
	}
}
