#ifndef _SORT_H
#define _SORT_H

/**
 * @brief Macro to calculate array's length.
 * @parma array It MUST be a array, passing a pointer won't work as you expact.
 * @return Size of the array.
 */
#define ARRAY_LEN(array) (sizeof(array)/sizeof(array[0]))

/**
 * @brief Insert Sort for array.
 *
 * Get a new card from unsorted group on right hand.
 * Insert it into the sorted group in left hand,
 * the Cards on left hand that greater than the new card are right shift by 1,
 * the new card goes in the empty slot after right shift.
 *
 * @note Complexity: O(n^2).
 * @parma array The array need to be sort.
 * @parma len Length of array.
 * @return The sorted array, Ascending.
 */
int *insert_sort (int *array, int len);

/**
 * @brief Select Sort for array.
 *
 * Find the minium element form 1st element in array , swap it with the 1st element,
 * find the minium element form 2end element in array, swap it with the 2nd element.
 * and so on...
 *
 * @note Complexity: O(n^2).
 * @parma array The array need to be sort.
 * @parma len Length of array.
 * @return The sorted array.
 */
int *selection_sort (int *array, int len);

int *merge_sort (int *array, int p, int r);

#endif /* _SORT_H */
