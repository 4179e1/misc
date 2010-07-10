#include <stdio.h>
#include <stdbool.h>
#include "mm.h"
#include "libmem.h"

#define WSIZE 	4
#define DSIZE	8
#define CHUNKSIZE (1 << 12)
#define OVERHEAD	8

#define MAX(x, y) ((x) > (y) ? (x) : (y))

#define PACK(size, alloc) ((size) | (alloc))

#define GET(P) (*(size_t *)(P))
#define PUT(P, VAL) (*(size_t *)(P) = (VAL))

#define GET_SIZE(P) (GET(P) & ~0x7)
#define GET_ALLOC(P) (GET(P) & 0x1)

#define HDRP(bp) ((char *)(bp) - WSIZE)
#define FTRP(Pbp) ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

#define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE)))
#define PREV_BLKP(bp) ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)))


static char *heap_listp;

static void *extend_heap (size_t words);
static void place (void *bp, size_t asize);
static void *find_fit (size_t asize);
static void *coalesce (void *bp);
static void printblock (void *bp);
static void checkblock (void *bp);

bool mm_init (void)
{
	if ((heap_listp = mem_sbrk (4 * WSIZE)) == NULL)
	{
		return false;
	}
	PUT (heap_listp, 0);
	PUT (heap_listp + WSIZE, PACK (OVERHEAD, 1));
	PUT (heap_listp + DSIZE, PACK (OVERHEAD, 1));
	PUT (heap_listp + WSIZE + DSIZE, PACK (0, 1));
	heap_listp += DSIZE;

	if (extend_heap (CHUNKSIZE/WSIZE) == NULL)
	{
		return false;
	}

	return true;
}

static void *extend_heap (size_t words)
{
	char *bp;
	size_t size;

	size = (words % 2) ? (words + 1) * WSIZE : words * WSIZE;
	if ((int)(bp = mem_sbrk (size)) < 0)
	{
		printf ("%s %d\n", __func__, __LINE__);
		return NULL;
	}

	PUT (HDRP(bp), PACK (size, 0));
	PUT (FTRP(bp), PACK (size, 0));
	PUT (HDRP (NEXT_BLKP (bp)), PACK (0, 1));

	return coalesce (bp);
}

void mm_free (void *bp)
{
	size_t size = GET_SIZE (HDRP (bp));

	PUT (HDRP (bp), PACK (size, 0));
	PUT (HDRP (bp), PACK (size, 0));
	coalesce (bp);
}

static void *coalesce (void *bp)
{
	size_t prev_alloc = GET_ALLOC (FTRP (PREV_BLKP (bp)));
	size_t next_alloc = GET_ALLOC (HDRP (NEXT_BLKP (bp)));
	size_t size = GET_SIZE (HDRP (bp));

	if (prev_alloc && next_alloc)
	{
		return bp;
	}
	else if (prev_alloc && !next_alloc)
	{
		size += GET_SIZE (HDRP (NEXT_BLKP (bp)));
		PUT (HDRP (bp), PACK (size, 0));
		PUT (FTRP (bp), PACK (size, 0));
		return bp;
	}
	else if (!prev_alloc && next_alloc)
	{
		size += GET_SIZE (HDRP (PREV_BLKP (bp)));
		PUT (FTRP (bp), PACK (size, 0));
		PUT (HDRP (PREV_BLKP (bp)), PACK (size, 0));
		return PREV_BLKP (bp);
	}
	else /* if !prev_alloc && !next_alloc */
	{
		size += GET_SIZE (HDRP (PREV_BLKP (bp))) + GET_SIZE (FTRP (NEXT_BLKP (bp)));
		PUT (HDRP (PREV_BLKP (bp)), PACK (size, 0));
		PUT (FTRP (PREV_BLKP (bp)), PACK (size, 0));
		return PREV_BLKP (bp);
	}
}

static void *find_fit (size_t asize)
{
	char *ptr = NEXT_BLKP (heap_listp);

	for (;GET_SIZE (HDRP (ptr)) != 0; ptr = NEXT_BLKP (ptr))
	{
		if (!GET_ALLOC (HDRP (ptr)) && GET_SIZE (HDRP (ptr)) >= asize)
		{
			return ptr;
		}
	}

	return NULL;
}

static void place (void *bp, size_t asize)
{
	size_t csize = GET_SIZE (HDRP (bp));

	if ((csize - asize) >= (DSIZE + OVERHEAD))
	{
		PUT (HDRP (bp), PACK (asize, 1));
		PUT (FTRP (bp), PACK (asize, 1));

		bp = NEXT_BLKP (bp);

		PUT (HDRP (bp), PACK (csize - asize, 0));
		PUT (FTRP (bp), PACK (csize - asize, 0));
	}
	else
	{
		PUT (HDRP (bp), PACK (csize, 1));
		PUT (FTRP (bp), PACK (csize, 1));
	}
}


void *mm_malloc (size_t size)
{
	size_t asize;
	size_t extendsize;
	char *bp;

	if (size <= 0)
	{
		return NULL;
	}

	if (size <= DSIZE)
	{
		asize = DSIZE + OVERHEAD;
	}
	else
	{
		asize = DSIZE * ((size + (OVERHEAD) + (DSIZE - 1)) / DSIZE);
	}

	if ((bp = find_fit (asize)) != NULL)
	{
		place (bp, asize);
		return bp;
	}

	extendsize = MAX (asize, CHUNKSIZE);

	if ((bp = extend_heap (extendsize/WSIZE)) == NULL)
	{
		printf ("%s %d\n", __func__, __LINE__);
		return NULL;
	}
	place (bp, asize);
	return bp;
}
