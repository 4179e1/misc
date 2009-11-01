#include <stdio.h>
#include "array_sort.h"

typedef int *(*array_sort_func)(int *array, int len);

static void print_array (int *array, int len);
static void sort (int *array, int len, array_sort_func func, char *name);

struct sort_data
{
	int *array;
	int len;
	array_sort_func func;
	char *name;
};

int main (void)
{
	int array1[] = {5, 2, 4, 6, 1, 3};
	int array2[] = {5, 2, 4, 6, 1, 3};

	struct sort_data data[] = 
	{
		{array1, ARRAY_LEN(array1), insert_sort, "Insert Sort"},
		{array2, ARRAY_LEN(array2), selection_sort, "Selection Sort"},
		{NULL, 0, NULL, NULL},
	};

	struct sort_data *ptr = data;
	while (ptr->array != NULL)
	{
		sort (ptr->array, ptr->len, ptr->func, ptr->name);
		ptr++;
	}

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

static void sort (int *array, int len, array_sort_func func, char *name)
{
	printf ("\n%s\n", name);
	printf ("Original array:\t");
	print_array (array, len);
	func (array, len);
	printf ("After sort:\t");
	print_array (array, len);
}
