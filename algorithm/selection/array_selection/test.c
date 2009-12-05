#include <stdio.h>
#include <string.h>
#include "array_selection.h"
#include "base.h"

int main (void)
{
	int array1[] = {4, 9, 3, 7, 1, 5};
	printf ("Min: %d\t Max: %d\n", minimum (array1, ARRAY_LEN (array1)), maximum (array1, ARRAY_LEN(array1)));

	int min, max;
	min_maximum (array1, ARRAY_LEN (array1), &min, &max);
	printf ("Min: %d\t Max: %d\n", min, max);


	printf ("randomized selection: %d\n", randomized_select (array1, 0, ARRAY_LEN(array1), 2));
	printf ("randomized selection loop: %d\n", randomized_select_loop (array1, 0, ARRAY_LEN(array1), 1));

	return 0;
}
