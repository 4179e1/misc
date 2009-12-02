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

	printf ("Dice(%dD%d) =", num, surface);
	for (i = 0; i < num; i++)
	{
		ran = random (1, surface);
		printf (" +%d", ran);
		cnt += ran;
	}

	printf (" = %d\n", cnt);
	return cnt;
}
