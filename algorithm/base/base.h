#ifndef _BASE_H
#define _BASE_H

#include <stdbool.h>
#include "wrap.h"
#include "int_func.h"

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

#define IS_ODD(n) ((n % 2) != 0)
#define IS_EVEN(n) ((n % 2) == 0)

#define INT_SENT_MAX 0x7fffffff
#define INT_SENT_MIN 0x80000000

typedef bool (*foreach_func_t) (void *elem, void *data);
typedef void (*write_func_t) (const void *elem, FILE *file);
typedef int (*compare_func_t) (const void *elem1, const void *elem2);

void print_array (int *array, int len);

void random_init (void);
int random_range (int a, int b);
int dice (int num, int surface);

int partition (int *array, int p, int r);
int randomized_partition (int *array, int p, int r);
#endif /* _BASE_H */
