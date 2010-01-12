#include <stdio.h>
#include "matrix.h"

int main (void)
{
	int i;
	int len = 6;
	Matrix *a[6] = 
	{
		matrix_new0 (30, 35),
		matrix_new0 (35, 15),
		matrix_new0 (15, 5),
		matrix_new0 (5, 10),
		matrix_new0 (10, 20),
		matrix_new0 (20, 25)
	};

	for (i = 0; i < len; i++)
	{
		matrix_free (a[i]);
	}

	return 0;
}
