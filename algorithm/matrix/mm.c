#include <stdio.h>
#include <assert.h>
#include "matrix.h"

#define MATRIX_LEN 2

void func1 (Matrix *a, Matrix *b, Matrix *c)
{
	printf ("%s\n", __func__);
	int i, j, k, sum;
	for (i = 1; i <= MATRIX_LEN; i++)
	{
		for (j = 1; j <= MATRIX_LEN; j++)
		{
			sum = 0;
			for (k = 1; k <= MATRIX_LEN; k++)
			{
				
				sum += matrix_get_value (a, i, k) * matrix_get_value (b, i, k);
			}
			matrix_set_value (c, i, j, sum);
		}
	}
	putchar ('\n');
}

void func2 (Matrix *a, Matrix *b, Matrix *c)
{
	printf ("%s\n", __func__);
	int i, j, k, sum;
	for (j= 1; j <= MATRIX_LEN; j++)
	{
		for (i = 1; i <= MATRIX_LEN; i++)
		{
			sum = 0;
			for (k = 1; k <= MATRIX_LEN; k++)
			{
				
				sum += matrix_get_value (a, i, k) * matrix_get_value (b, i, k);
			}
			matrix_set_value (c, i, j, sum);
		}
	}
	putchar ('\n');
}

void func3 (Matrix *a, Matrix *b, Matrix *c)
{
	printf ("%s\n", __func__);
	int i, j, k, r;
	for (j = 1; j <= MATRIX_LEN; j++)
	{
		for (k = 1; k <= MATRIX_LEN; k++)
		{
			r = matrix_get_value (b, k, j);
			for (i = 1; i <= MATRIX_LEN; i++)
			{
				matrix_add_equal_value (c, i, j, (matrix_get_value (a, i, k) * r));
			}
		}
	}
	putchar ('\n');
}

void func5 (Matrix *a, Matrix *b, Matrix *c)
{
	printf ("%s\n", __func__);
	int i, j, k, r;
	for (k = 1; k <= MATRIX_LEN; k++)
	{
		for (i = 1; i <= MATRIX_LEN; i++)
		{
			r = matrix_get_value (a, i, k);
			for (j = 1; j <= MATRIX_LEN; j++)
			{
				matrix_add_equal_value (c, i, j, (r * matrix_get_value (b, k, j)));
			}
		}
	}

	putchar ('\n');
}


int main (void)
{
	Matrix *a = matrix_new (MATRIX_LEN, MATRIX_LEN, 1);
	Matrix *b = matrix_new (MATRIX_LEN, MATRIX_LEN, 2);
	Matrix *c = matrix_new0 (MATRIX_LEN, MATRIX_LEN);

	matrix_set_name (a, "A");
	matrix_set_name (b, "B");
	matrix_set_name (c, "C");

	assert (a != NULL);
	assert (b != NULL);
	assert (c != NULL);

	func1 (a, b, c);
	func2 (a, b, c);
	func3 (a, b, c);

	func5 (a, b, c);

	matrix_free (a);
	matrix_free (b);
	matrix_free (c);
	
	return 0;
}
