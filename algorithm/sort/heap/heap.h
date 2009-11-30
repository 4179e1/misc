#ifndef _HEAP_H
#define _HEAP_H

typedef struct _heap Heap;

typedef enum _heap_type
{
	MAX_HEAP = 0,
	MIN_HEAP,
} HeapType;

/* use heap_free() to free the return value */
Heap *heap_new(HeapType type, int size);
/* use free() */
Heap *heap_new_from_array (HeapType type, int *array, int len);

void heap_free (Heap *heap);

int *heap_sort (int *array, int len);

#endif /* _HEAP_H */
