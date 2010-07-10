#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "mm.h"
#include "libmem.h"

int main (void)
{
	mem_init (1<<13);
	if (!mm_init ())
	{
		fprintf (stderr, "mm_init() error\n");
		exit (-1);
	}

	char *ptr = (char *)mm_malloc (1<<10);
	assert (ptr != NULL);

	int i;

	for (i = 0; i < 1 << 10; i++)
	{
		ptr[i] = i;
		printf ("%d\n", i);
	}

	mm_free (ptr);
	return 0;
}
