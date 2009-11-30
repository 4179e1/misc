#include "heap.h"
#include "base.h"

int main (void)
{
	int array[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
	heap_sort (array, ARRAY_LEN(array));
	print_array (array, ARRAY_LEN(array));
	return 0;
}
