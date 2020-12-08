#ifndef _HEAP_H
#define _HEAP_H

#include <stdio.h>
#include <stdbool.h>

typedef struct _heap Heap;

typedef enum _heap_type
{
	MAX_HEAP = 0,
	MIN_HEAP,
} HeapType;

/* use heap_free() to free the return value */
Heap *heap_new(HeapType type, int size);
void heap_free (Heap *heap);
void heap_dump (Heap *heap, FILE *file);
bool heap_is_empty (Heap *heap);

HeapType heap_get_type (Heap *heap);
int heap_get_size (Heap *heap);
int heap_get_card (Heap *heap);
int heap_get_growing_factor (Heap *heap);
void heap_set_growing_factor (Heap *heap, int value);

/* prority queue */
/**
 * @brief insert a value to heap
 * @note Complexity O( lg(n) )
 */
void heap_insert (Heap *heap, int value);
/**
 * @breif return the root element
 * @note Complexity O( 1 )
 * @return for MAX_HEAP, return the largest; for MIN_HEAP, return the minimum.
 */
int heap_root (Heap *heap);

/**
 * @breif delete and return the root element
 * @note Complexity O( lg(n) )
 * @return for MAX_HEAP, delete & return the largest in heap;
 *		   for MIN_HEAP, delete & return the minimum in heap.
 * @see heap_root().
 */
int heap_extract_root (Heap *heap);

/**
 * @brief set an element in heap wiht another value;
 *
 * for MAX_HEAP, require key > current value in index i;
 * for MIN_HEAP, require key < current value in index i;
 *
 * @note Complexity O( lg(n) )
 * @param heap 
 * @param i index of the element to set.
 * @param key new value set to element.
 */
void heap_update_key (Heap *heap, int i, int key);

/* heap sort func */
/**
 * @brief Heap sort
 *
 * Swap the first elem which is the largest in heap with last elem of heap,
 * decrease heap size by 1, loop until heap size is 0.
 * 
 * @note Complexity O( n*lg(n) )
 * @param array the array need to sort.
 * @param len length of array.
 * @return sorted array.
 */
int *heap_sort (int *array, int len);
#endif /* _HEAP_H */
