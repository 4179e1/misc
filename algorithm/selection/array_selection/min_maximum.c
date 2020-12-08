#include "array_selection.h"
#include "base.h"

int minimum (int *array, int len)
{
	int i;
	int min = array[0];
	for (i = 1; i < len; i++)
	{
		if (min > array[i])
		{
			min = array[i];
		}
	}
	return min;
}

int maximum (int *array, int len)
{
	int i;
	int max = array[0];
	for (i = 1; i < len; i++)
	{
		if (max < array[i])
		{
			max = array[i];
		}
	}
	return max;
}

void min_maximum (int *array, int len, int *min, int *max)
{
	int i, largest, smallest;
	if (len < 2)
	{
		*min = *max = array[0];
		return;
	}
	
	if (IS_ODD (len))
	{
		smallest = largest = array[0];
		i = 1;
	}
	else	/* IS_EVEN */
	{
		smallest = MIN (array[0], array[1]);
		largest = MAX (array[0], array[1]);
		i = 2;
	}

	while (i < len)
	{
		if (array[i] < array[i + 1])
		{
			smallest = MIN (smallest, array[i]);
			largest = MAX (largest, array[i + 1]);
		}
		else /* array[i] > array[i + 1] */
		{
			smallest = MIN (smallest, array[i + 1]);
			largest = MAX (largest, array[i]);
		}
		i += 2;
	}

	*min = smallest;
	*max = largest;
}
