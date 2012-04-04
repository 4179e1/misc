#include <stdio.h>
#include <string.h>
#include "array_sort.h"
#include "base.h"

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

	int arrayz[] = {7, 0, 9, 3, 9, 4};
	printf ("quick sort\n");
	quick_sort (arrayz, 0, ARRAY_LEN(arrayz) - 1);
	print_array (arrayz, ARRAY_LEN(arrayz));

	int array6[] = {2, 8, 7, 1, 3, 5, 6};
	printf ("randomized quick sort\n");
	randomized_quick_sort (array6, 0, ARRAY_LEN(array6) - 1);
	print_array (array6, ARRAY_LEN(array6));

	int array7[] = {2, 8, 7, 1, 3, 5, 6};
	printf ("tail quick sort\n");
	tail_quick_sort (array7, 0, ARRAY_LEN(array7) - 1);
	print_array (array7, ARRAY_LEN(array7));

	int a[] = {2, 5, 3, 0, 2, 3, 0, 3};
	int b[ARRAY_LEN(a)];
	memset (b, 0, sizeof(b));
	printf ("counting sort\n");
	counting_sort (a, b, ARRAY_LEN(a), ARRAY_LEN(b), 5);
	print_array (b, ARRAY_LEN(b));

	return 0;
}
