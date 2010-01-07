#include <stdio.h>
#include "int_func.h"

int int_cmp (const void *i, const void *j)
{
	return (*(int *)i - *(int *)j);
}

void int_write (const void *i, FILE *file, void *data)
{
	fprintf (file, "%d", *(int *)i);
}
