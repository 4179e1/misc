#include <stdio.h>
#include "array_sort.h"

static void print_array (int *array, int len);

int main (void)
{
	int array1[] = {5, 2, 4, 6, 1, 3};
	printf ("Insert Sort\n");
	insert_sort (array1, ARRAY_LEN(array1));
	print_array (array1, ARRAY_LEN(array1));

	int array2[] = {5, 2, 4, 6, 1, 3};
	printf ("Selection Sort\n");
	selection_sort (array2, ARRAY_LEN (array2));
	print_array (array2, ARRAY_LEN (array2));


	int array3[] = {5, 2, 4, 6, 1, 3};
	printf ("Merge Sort\n");
	merge_sort (array3, 0, ARRAY_LEN(array3) - 1);
	print_array (array3, ARRAY_LEN(array3));

	int array4[] = {5, 2, 4, 6, 1, 3};
	printf ("Bubble sort\n");
	bubble_sort (array4, ARRAY_LEN(array4));
	print_array (array4, ARRAY_LEN(array4));

	return 0;
}

static void print_array (int *array, int len)
{
	int i;
	for (i = 0; i < len; i++)
	{
		printf (" %d", array[i]);
	}

	printf ("\tEOA\n");
}
