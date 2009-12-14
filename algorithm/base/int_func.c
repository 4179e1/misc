#include <stdio.h>
#include "int_func.h"

int int_cmp (void *i, void *j)
{
	return (*(int *)i - *(int *)j);
}

void int_write (void *i, FILE *file)
{
	fprintf (file, "%d", *(int *)i);
}
