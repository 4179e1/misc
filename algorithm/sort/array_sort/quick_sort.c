#include "array_sort.h"
#include "base.h"

static int partition (int *array, int p, int r);
static int randomized_partition (int *array, int p, int r);

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

/* private func */
static int partition (int *array, int p, int r)
{
	int i, j, x;
	x = array[r];
	i = p - 1;

	for (j = p; j < r; j++)
	{
		if (array[j] < x)
		{
			i++;
			swap (&array[j], &array[i]);
		}
	}

	swap (&array[i + 1], &array[r]);
	return i + 1;
}

static int randomized_partition (int *array, int p, int r)
{
	int i = random (p, r);
	swap (&array[i], &array[r]);
	return partition (array, p, r);
}
