#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "base.h"

void swap (int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void print_array (int *array, int len)
{
	int i;
	for (i = 0; i < len; i++)
	{
		printf (" %d", array[i]);
	}

	printf ("\tEOA\n");
}

void random_init (void)
{
	srand ((unsigned int)time (NULL));
}

int random (int a, int b)
{
	return (rand()%(b - a + 1) + a);
}

int dice (int num, int surface)
{
	int cnt = 0;
	int ran;
	int i;

	printf ("Dice(%dD%d): ", num, surface);
	for (i = 0; i < num; i++)
	{
		ran = random (1, surface);
		printf ("%d + ", ran);
		cnt += ran;
	}

	printf ("\b\b= %d\n", cnt);
	return cnt;
}

/** 
 * @brief partition for quick sort
 * 
 * Select the last element as the Q value, elements between index i and j
 * are smaller than Q, elements between index j and (r - 1) are greater than
 * or equal to Q. Swap Q with the elements in index (i + 1). return index of Q.
 *
 * @note Complexity O ( n )
 * @return Index of Q value.
 */
int partition (int *array, int p, int r)
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

/** 
 * @brief randomized partition for randomized quick sort
 * 
 * select a random element in array as the Q value.
 *
 * @note Complexity O ( n )
 */
int randomized_partition (int *array, int p, int r)
{
	int i = random (p, r);
	swap (&array[i], &array[r]);
	return partition (array, p, r);
}
