#ifndef _ARRAY_SELECTION_H
#define _ARRAY_SELECTION_H

int minimum (int *array, int len);
int maximum (int *array, int len);
void min_maximum (int *array, int len, int *min, int *max);

int randomized_select (int *array, int p, int r, int i);
int randomized_select_loop (int *array, int p, int r, int i);
#endif /* _ARRAY_SELECTION_H */
