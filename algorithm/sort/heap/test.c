#include "heap.h"
#include "base.h"

int main (void)
{
	int array[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};

	int i;

	{
		Heap *heap = heap_new (MAX_HEAP, 20);
	
		for (i = 0; i < ARRAY_LEN(array); i++)
		{
			heap_insert (heap, array[i]);
		}
		heap_dump (heap, stdout);
		
		while (!heap_is_empty (heap))
		{
			printf ("%d ", heap_extract_root (heap));
		}
		printf ("\n");
	}

	{
		Heap *h2 = heap_new (MIN_HEAP, 1);
	
		for (i = 0; i < ARRAY_LEN(array); i++)
		{
			heap_insert (h2, array[i]);
		}
		heap_dump (h2, stdout);
		
		while (!heap_is_empty (h2))
		{
			printf ("%d ", heap_extract_root (h2));
		}
		printf ("\n");
	}

	{
		heap_sort (array, ARRAY_LEN(array));
		print_array (array, ARRAY_LEN(array));
	}
	return 0;
}
