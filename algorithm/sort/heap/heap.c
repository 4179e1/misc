#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "heap.h"
#include "base.h"

typedef void (*heapify_func_t) (Heap *heap, int index);

struct _heap 
{
	int *data;
	int card;
	int size;
	heapify_func_t heapify_func;
};

#define HEAP_PARENT_INDEX(i) ((i - 1) / 2)
#define HEAP_LEFT_INDEX(i) (2 * i + 1)
#define HEAP_RIGHT_INDEX(i) (2 * i + 2)

static void max_heapify (Heap *heap, int index);
static void min_heapify (Heap *heap, int index);

Heap *heap_new (HeapType heap_type, int size)
{
	Heap *h;

	h = (Heap *)malloc (sizeof (Heap));
	if (h == NULL)
	{
		return NULL;
	}

	h->data = (int *)malloc (sizeof(int) *size);
	if (h->data == NULL)
	{
		free (h);
		return NULL;
	}
	
	h->card = 0;
	h->size = size;

	h->heapify_func = (heap_type == MAX_HEAP) ? max_heapify : min_heapify;

	return h;
}

Heap *heap_new_from_array (HeapType heap_type, int *array, int size)
{
	Heap *h;
	int i;

	assert (array != NULL);

	h = (Heap *)malloc (sizeof (Heap));
	if (h == NULL)
	{
		return NULL;
	}

	h->data = array;
	h->size = size;
	h->heapify_func = (heap_type == MAX_HEAP) ? max_heapify : min_heapify;

	h->card = size;
	for (i = HEAP_PARENT_INDEX (h->card); i >= 0; i--)
	{
		h->heapify_func (h, i);
	}
	
	return h;
}

void heap_free (Heap *h)
{
	free (h->data);
	free (h);
}

int *heap_sort (int *array, int len)
{
	Heap *h;
	int i;

	assert (array != NULL);

	h = heap_new_from_array (MAX_HEAP, array, len);
	for (i = len - 1; i > 0; i--)
	{
		swap (&array[0], &array[i]);
		(h->card)--;
		h->heapify_func (h, 0);
	}

	free (h);
	return array;
}

/* private func */
static void max_heapify (Heap *h, int i)
{
	int l, r, largest;

	assert (h != NULL);

	l = HEAP_LEFT_INDEX (i);
	r = HEAP_RIGHT_INDEX (i);

	if ((l < h->card) && (h->data[l] > h->data[i]))
	{
		largest = l;
	}
	else
	{
		largest = i;
	}

	if ((r < h->card) && (h->data[r] > h->data[largest]))
	{
		largest = r;
	}

	if (largest != i)
	{
		swap (&(h->data[i]), &(h->data[largest]));
		max_heapify (h, largest);
	}
}

static void min_heapify (Heap *h, int i)
{
	int l, r, minimum;

	assert (h != NULL);

	l = HEAP_LEFT_INDEX (i);
	if ((l < h->card) && (h->data[l] < h->data[i]))
	{
		minimum = l;
	}
	else
	{
		minimum = i;
	}

	if ((r < h->card) && (h->data[r] < h->data[minimum]))
	{
		minimum = r;
	}

	if (minimum != i)
	{
		swap (&(h->data[i]), &(h->data[minimum]));
		min_heapify (h, minimum);
	}
}
