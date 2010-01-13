#include <stdio.h>
#include "matrix.h"

int main (void)
{
	int i;
	int len = 6;
	Matrix *aout;

	Matrix *a[6] = 
	{
		matrix_new (30, 35, 1),
		matrix_new (35, 15, 1),
		matrix_new (15, 5, 1),
		matrix_new (5, 10, 1),
		matrix_new (10, 20, 1),
		matrix_new (20, 25, 1)
	};
	

	//matrix_chain_print_optimal_multiply_parens (a, len);

	aout = matrix_chain_multiply (a, len);
	matrix_write (aout, stdout);

	for (i = 0; i < len; i++)
	{
		matrix_free (a[i]);
	}

	return 0;
}
