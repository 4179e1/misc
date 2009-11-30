#include "heap.h"
#include "base.h"

int main (void)
{
	int array[] = {5, 2, 1, 3, 4, 6};
	heap_sort (array, ARRAY_LEN(array));
	print_array (array, ARRAY_LEN(array));
	return 0;
}
