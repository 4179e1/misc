#ifndef _BASE_H
#define _BASE_H

/**
 * @brief Macro to calculate array's length.
 * @param array It MUST be a array, passing a pointer won't work as you expact.
 * @return Size of the array.
 */
#define ARRAY_LEN(array) (sizeof(array)/sizeof(array[0]))

/** 
 * @beief Inline func for swapping two integer
 *
 * @param a, b Pointer to integer 
 */
void swap (int *a, int *b);

#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a < b) ? a : b)

void print_array (int *array, int len);
#endif /* _BASE_H */
