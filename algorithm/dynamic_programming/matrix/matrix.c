#include <stdlib.h>
#include <assert.h>
#include "matrix.h"

#define INT_MAX_SENTINEL 0x7fffffff

static void matrix_chain_multiply_order (Matrix *ma[], int len, Matrix *m, Matrix *s);
static void matrix_chain_print_optimal_parens (Matrix *s, int i, int j);
static Matrix *matrix_chain_optimal_multiply (Matrix *ma[], Matrix *s, int i, int j);
static int matrix_chain_get_dimensions (Matrix *ma[], int len, int pos1, int pos2, int pos3);
static int matrix_chain_get_dimension (Matrix *ma[], int len, int pos);

struct _matrix
{
	int row;
	int column;
	int ref;
	int *data;
};

Matrix *matrix_new (int row, int column, int value)
{
	Matrix *m;
	int i, j;

	assert (column > 0);
	assert (row > 0);

	m = (Matrix *)malloc (sizeof (Matrix));
	if (m == NULL)
	{
		fprintf (stderr, "malloc() error\n");
		return NULL;
	}

	m->data = (int *)malloc (sizeof (int) * row * column);
	if (m->data == NULL)
	{
		fprintf (stderr, "malloc() error\n");
		free (m);
		return NULL;
	}

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < column; j++)
		{
			(m->data)[i * column + j] = value;
		}
	}

	m->row = row;
	m->column = column;
	m->ref = -1;

	return m;
}

void matrix_free (Matrix *m)
{
	assert (m != NULL);
	free (m->data);
	free (m);
}

int matrix_get_row (Matrix *m)
{
	assert (m != NULL);
	return m->row;
}

int matrix_get_column (Matrix *m)
{
	assert (m != NULL);
	return m->column;
}

void matrix_ref (Matrix *m)
{
	assert (m != NULL);
	if (m->ref < 0)
	{
		return;
	}

	(m->ref)++;
}

void matrix_unref (Matrix *m)
{
	assert (m != NULL);
	if (m->ref < 0)
	{
		return;
	}

	if (--(m->ref) == 0)
	{
		free (m->data);
		free (m);
	}
}

void matrix_set_value (Matrix *m, int row, int column, int value)
{
	assert (m != NULL);
	assert (row > 0);
	assert (column > 0);

	if (row > m->row || column > m->column)
	{
		return;
	}

	m->data[(row - 1) * (m->column) + (column - 1)] = value;
}

int matrix_get_value (Matrix *m, int row, int column)
{
	assert (m != NULL);
	assert (row > 0);
	assert (column > 0);
	if (row > m->row || column > m->column)
	{
		return -1;
	}
	return m->data[(row - 1) * (m->column) + (column - 1)];
	return 0;
}

void matrix_set_all_value (Matrix *m, int value)
{
	int i, j;

	assert (m != NULL);

	for (i = 0; i < m->column; i++)
	{
		for (j = 0; j < m->row; j++)
		{
			m->data[i * (m->column) + j] = value;
		}
	}
}

Matrix *matrix_multiply (Matrix *a, Matrix *b)
{
	int i, j, k;
	Matrix *c = NULL;

	assert (a != NULL);
	assert (b != NULL); 

	if (a->column == b->row)
	{
		c = matrix_new (a->row, b->column, 0);
		if (c == NULL)
		{
			return NULL;
		}
		c->ref = 1;
		
		for (i = 0; i < a->row; i++)
		{
			for (j = 0; j < b->column; j++)
			{
			 	for (k = 0; k < a->column; k++)
				{
					c->data[i * (c->column) + j] += (a->data[i * (a->column) + k] * b->data[k *(b->column) + j]);
				}
			}
		}
		matrix_unref (a);
		matrix_unref (b);
	}

	return c;
}

Matrix *matrix_chain_multiply (Matrix *ma[], int len)
{
	Matrix *m;
	Matrix *s;
	Matrix *rst;

	assert (ma != NULL);
	assert (len > 0);

	m = matrix_new (len, len, -1);
	s = matrix_new (len, len, -1);

	matrix_chain_multiply_order (ma, len, m, s);

	rst = matrix_chain_optimal_multiply (ma, s, 1, len);

	matrix_free (m);
	matrix_free (s);

	return rst;
}

void matrix_chain_print_optimal_multiply_parens (Matrix *ma[], int len)
{
	Matrix *m;
	Matrix *s;

	assert (ma != NULL);
	assert (len > 0);

	m = matrix_new (len, len, -1);
	s = matrix_new (len, len, -1);

	matrix_chain_multiply_order (ma, len, m, s);

	matrix_chain_print_optimal_parens (s, 1, len);
	printf ("\n");

	matrix_free (m);
	matrix_free (s);
}

Matrix *matrix_add (Matrix *a, Matrix *b)
{
	int i, j;
	Matrix *c = NULL;

	assert (a != NULL);
	assert (b != NULL);

	if (a->row == b->column && a->row == b->column)
	{
		c = matrix_new (a->row, a->column, 0);
		if (c == NULL)
		{
			return NULL;
		}
		c->ref = 1;

		for (i = 0; i < a->row; i++)
		{
			for (j = 0; j < a->column; j++)
			{
				c->data[i * (c->column) + j] += (a->data[i * (a->column) + j] + b->data[i * (b->column) + j]);
			}
		}
		matrix_unref (a);
		matrix_unref (b);
	}

	return c;
}

void matrix_dump (Matrix *m, FILE *file)
{
	int i, j;

	assert (m != NULL);
	assert (file != NULL);

	fprintf (file, "<MATRIX ROW=\"%d\" COLUMN=\"%d\">\n", m->row, m->column);
	for (i = 0; i < m->row; i++)
	{
		fprintf (file, "<ROW%d>", i + 1);
		for (j = 0; j < m->column; j++)
		{
			fprintf (file, "<COL%d>%d</COL%d>", j + 1, m->data[i * m->column + j], j + 1);
		}
		fprintf (file, "</ROW%d>\n", i + 1);
	}
	fprintf (file, "</MATRIX>\n");
}

void matrix_write (Matrix *m, FILE *file)
{
	int i, j;
	assert (m != NULL);
	assert (file != NULL);

	for (i = 0; i < m->row; i++)
	{
		for (j = 0; j < m->column; j++)
		{
			fprintf (file, "%d\t", m->data[i * m->column + j]);
		}
		fprintf (file, "\n");
	}
}

void matrix_foreach (Matrix *m, void (*f)(int *elem, void *data), void *data)
{
	int i, j;

	assert (m != NULL);
	assert (f != NULL);

	for (i = 0; i < m->row; i++)
	{
		for (j = 0; j < m->column; j++)
		{
			f (&(m->data[i * (m->column + j)]), data);
		}
	}
}

/* private func */

void matrix_chain_multiply_order (Matrix *ma[], int len, Matrix *m, Matrix *s)
{
	int i, j, k, l;
	int q;
	int n = len;

	for (i = 1; i <= n; i++)
	{
		matrix_set_value (m, i, i, 0);
	}

	for (l = 2; l <= n; l++)
	{
		for (i = 1; i <= (n - l + 1); i++)
		{
			j = (i + l - 1);
			matrix_set_value (m, i, j, INT_MAX_SENTINEL);
			for (k = i; k <= (j - 1); k++)
			{
				q = matrix_get_value (m, i, k) + matrix_get_value (m, k + 1, j) + matrix_chain_get_dimensions (ma, len, i - 1, k, j);
				if (q < matrix_get_value (m, i, j))
				{
					matrix_set_value (m, i, j, q);
					matrix_set_value (s, i, j, k);
				}
			}
		}
	}
}

static int matrix_chain_get_dimensions (Matrix *ma[], int len, int pos1, int pos2, int pos3)
{
	int p1 = matrix_chain_get_dimension (ma, len, pos1);
	int p2 = matrix_chain_get_dimension (ma, len, pos2);
	int p3 = matrix_chain_get_dimension (ma, len, pos3);

	return p1 * p2 * p3;
}

static int matrix_chain_get_dimension (Matrix *ma[], int len, int pos)
{
	assert (pos <= len);
	if (pos == len)
	{
		return ma[pos - 1]->column;
	}
	else
	{
		return ma[pos]->row;
	}
}

static void matrix_chain_print_optimal_parens (Matrix *s, int i, int j)
{
	if (i == j)
	{
		printf ("A%d", i);
	}
	else
	{
		printf ("(");
		matrix_chain_print_optimal_parens (s, i, matrix_get_value (s, i, j));
		matrix_chain_print_optimal_parens (s, matrix_get_value (s, i, j) + 1, j);
		printf (")");
	}
}

static Matrix *matrix_chain_optimal_multiply (Matrix *ma[], Matrix *s, int i, int j)
{
	int split;
	Matrix *l;
	Matrix *r;

	if (i == j)
	{
		return (ma[i - 1]);
	}
	else
	{
		split = matrix_get_value (s, i, j);
		l = matrix_chain_optimal_multiply (ma, s, i, split);
		r = matrix_chain_optimal_multiply (ma, s, split + 1, j);
		return (matrix_multiply (l, r));
	}
}
