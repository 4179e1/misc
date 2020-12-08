#ifndef _SORT_H
#define _SORT_H

int *insert_sort (int *array, int len);

int *selection_sort (int *array, int len);

int *merge_sort (int *array, int p, int r);

int *bubble_sort (int *array, int len);

void quick_sort (int *array, int p, int r);
void randomized_quick_sort (int *array, int p, int r);
void tail_quick_sort (int *array, int p, int r);

int *counting_sort (int *a, int *b, int len_a, int len_b, int k);
#endif /* _SORT_H */
