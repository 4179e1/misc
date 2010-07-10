#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include "libmem.h"

static char *mem_start_brk;
static char *mem_brk;
static char *mem_max_addr;

void mem_init (unsigned int size)
{
	mem_start_brk = (char *)malloc (size);
	if (mem_start_brk == NULL)
	{
		fprintf (stderr, "malloc() error\n");
		exit (-1);
	}
	mem_brk = mem_start_brk;
	mem_max_addr = mem_start_brk + size;
}

void *mem_sbrk (unsigned int incr)
{
	char *old_brk = mem_brk;

	if ((mem_brk + incr) > mem_max_addr)
	{
		printf ("%s %d\n", __func__, __LINE__);
		errno = ENOMEM;
		return (void *)-1;
	}

	mem_brk += incr;
	return old_brk;
}
