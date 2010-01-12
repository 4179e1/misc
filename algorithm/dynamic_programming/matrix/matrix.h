#ifndef _MATRIX_H
#define _MATRIX_H
#include <stdio.h>

typedef struct _matrix Matrix;

Matrix *matrix_new (int row, int cloumn, int value);
#define matrix_new0(M, N) (matrix_new(M, N, 0))
void matrix_free (Matrix *m);

int matrix_get_row (Matrix *m);
int matrix_get_column (Matrix *m);

void matrix_ref (Matrix *m);
void matrix_unref (Matrix *m);

void matrix_set_value (Matrix *m, int row, int column, int value);
int matrix_get_value (Matrix *m, int row, int column);

void matrix_set_all_value (Matrix *m, int value);

Matrix *matrix_multi (Matrix *a, Matrix *b);
Matrix *matrix_add (Matrix *a, Matrix *b);

void matrix_write (Matrix *m, FILE *file);
void matrix_foreach (Matrix *m, void (*f)(int *elem, void *data), void *data);

#endif /* _MATRIX_H */
