#include <stdio.h>
#include <stdlib.h>
#include "wrap.h"

void *Malloc (size_t size)
{
	void *ptr;
	if ((ptr = malloc (size)) == NULL)
	{
		fprintf (stderr, "malloc error\n");
	}
	return ptr;
}

void *Realloc (void *ptr, size_t size)
{
	void *p;
	if ((p = realloc (ptr, size)) == NULL)
	{
		fprintf (stderr, "realloc error\n");
	}
	return p;
}
