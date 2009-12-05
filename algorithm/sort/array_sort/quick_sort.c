#include "array_sort.h"
#include "base.h"

/**
 * @brief quick sort
 * 
 * @note Complexity O ( n*lg(n) )
 */
void quick_sort (int *array, int p, int r)
{
	int q;
	if (p < r)
	{
		q = partition (array, p, r);
		quick_sort (array, p, q - 1);
		quick_sort (array, q + 1, r);
	}
}

void randomized_quick_sort (int *array, int p, int r)
{
	int q;
	if (p < r)
	{
		q = randomized_partition (array, p, r);
		randomized_quick_sort (array, p, q - 1);
		randomized_quick_sort (array, q + 1, r);
	}
}

void tail_quick_sort (int *array, int p, int r)
{
	int q;
	while (p < r)
	{
		q = partition (array, p, r);
		tail_quick_sort (array, p, q - 1);
		p = q + 1;
	}
}
