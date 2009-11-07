#ifndef _SORT_H
#define _SORT_H

/**
 * @brief Macro to calculate array's length.
 * @parma array It MUST be a array, passing a pointer won't work as you expact.
 * @return Size of the array.
 */
#define ARRAY_LEN(array) (sizeof(array)/sizeof(array[0]))

/** 
 * @beief Inline func for swapping two integer
 *
 * @parma a, b Pointer to integer 
 */
static inline void swap (int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

int *insert_sort (int *array, int len);

int *selection_sort (int *array, int len);

int *merge_sort (int *array, int p, int r);

#endif /* _SORT_H */
