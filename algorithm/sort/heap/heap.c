#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdlib.h>
#include "heap.h"
#include "base.h"

typedef void (*heapify_func_t) (Heap *heap, int index);

struct _heap 
{
	int *data;
	HeapType type;
	int size;
	int card;
	int growing_factor;
	heapify_func_t heapify_func;
};

#define HEAP_PARENT_INDEX(i) ((i - 1) / 2)
#define HEAP_LEFT_INDEX(i) (2 * i + 1)
#define HEAP_RIGHT_INDEX(i) (2 * i + 2)

static void max_heapify (Heap *heap, int index);
static void min_heapify (Heap *heap, int index);
static void max_heapify_loop (Heap *h, int i);
static void min_heapify_loop (Heap *h, int i);
static Heap *heap_new_from_array (HeapType heap_type, int *array, int size);

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
	
	h->growing_factor = 10;
	h->card = 0;
	h->size = size;
	h->type = heap_type;

	h->heapify_func = (heap_type == MAX_HEAP) ? max_heapify : min_heapify;

	return h;
}

void heap_free (Heap *h)
{
	free (h->data);
	free (h);
}

void heap_dump (Heap *h, FILE *file)
{
	int i;
	assert (h != NULL);

	fprintf (file, "<HEAP TYPE=\"%s\" SIZE=\"%d\" CARD=\"%d\" GROWING_FACTOR=\"%d\">",
			((h->type == MAX_HEAP) ? "MAX-HEAP" : "MIN-HEAP"), h->size, h->card, h->growing_factor);
	for (i = 0; i < h->card; i++)
	{
		fprintf (file, "<NODE>%d</NODE>", h->data[i]);
	}
	fprintf (file, "</HEAP>\n");
}

bool heap_is_empty (Heap *h)
{
	return (h->card == 0);
}

HeapType heap_get_type (Heap *heap)
{
	assert (heap != NULL);
	return heap->type;
}

int heap_get_size (Heap *heap)
{
	assert (heap != NULL);
	return heap->size;
}

int heap_get_card (Heap *heap)
{
	assert (heap != NULL);
	return heap->card;
}

int heap_get_growing_factor (Heap *heap)
{
	assert (heap != NULL);
	return heap->growing_factor;
}

void heap_set_growing_factor (Heap *heap, int value)
{
	assert (heap != NULL);
	heap->growing_factor = value;
}

void heap_insert (Heap *h, int v)
{
	assert (h != NULL);

	(h->card)++; /* avoiding array bounds exceeded*/
	if (h->card > h->size)
	{
		h->data = realloc (h->data, (h->size + h->growing_factor)*sizeof(int));
		if (h->data == NULL)
		{
			fprintf (stderr, "realloc error");
			return;
		}
		h->size += h->growing_factor;
	}

	if (h->type == MAX_HEAP)
	{
		h->data[h->card - 1] = INT_SENT_MIN;
	}
	else
	{
		h->data[h->card - 1] = INT_SENT_MAX;
	}
	heap_update_key (h, h->card - 1, v);
}

/* priority queue*/

int heap_root (Heap *h)
{
	assert (h != NULL);
	return h->data[0];
}

int heap_extract_root (Heap *h)
{
	int val;
	assert (h != NULL);

	if (h->card < 0)
	{
		fprintf (stderr, "error: heap empty\n");
		exit (-1);
	}
	
	val = h->data[0];
	h->data[0] = h->data[(h->card) - 1];
	(h->card)--;
	h->heapify_func (h, 0);

	return val;
}
void heap_update_key (Heap *h, int i, int key)
{
	if (h->type == MAX_HEAP)
	{
		if (key < h->data[i])
		{
			fprintf (stderr, "Max-Heap: new key %d is samller than current key %d\n", key, h->data[i]);
			return;
		}

		h->data[i] = key;
		while ((i > 0) && (h->data[HEAP_PARENT_INDEX(i)] < h->data[i]))
		{
			swap (&(h->data[HEAP_PARENT_INDEX(i)]), &(h->data[i]));
			i = HEAP_PARENT_INDEX (i);
		}
	}
	else
	{
		if (key > h->data[i])
		{
			fprintf (stderr, "Min-Heap: new key %d is larger than current key %d\n", key, h->data[i]);
			return;
		}
		h->data[i] = key;
		while ((i > 0) && (h->data[HEAP_PARENT_INDEX(i)] > h->data[i]))
		{
			swap (&(h->data[HEAP_PARENT_INDEX(i)]), &(h->data[i]));
			i = HEAP_PARENT_INDEX (i);
		}
	}
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

/*******************************************************
 * private func
 ******************************************************/

/**
 * @breaif heapify a heap
 * 
 * Assuming the two child tree rooted at HEAP_LEFT_INDEX (i) and
 * HEAP_RIGHT_INDEX (i) are max-heaps. 
 *
 * @note Complexity: O( lg(n) )
 * @param h the heap need to heapify
 * @param i the position need to heapify
 */
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

/**
 * @see max_heapify
 */
static void min_heapify (Heap *h, int i)
{
	int l, r, minimum;

	assert (h != NULL);

	l = HEAP_LEFT_INDEX (i);
	r = HEAP_RIGHT_INDEX (i);
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

/**
 * @brief loop version of max_heapify, should be faster.
 * @see max_heapify().
 */
static void max_heapify_loop (Heap *h, int i)
{
	int l, r, largest;
	int tmp = i;

	/* save the previous value of tmp */
	int p;

	do {
		p = tmp;
		l = HEAP_LEFT_INDEX (tmp);
		r = HEAP_RIGHT_INDEX (tmp);

		if ((l < h->card) && (h->data[l] > h->data[tmp]))
		{
			largest = l;
		}
		else
		{
			largest = tmp;
		}

		if ((r < h->card) && (h->data[r] > h->data[largest]))
		{
			largest = r;
		}

		if (largest != tmp)
		{
			swap (&(h->data[tmp]), &(h->data[largest]));
			tmp = largest;
		}
	} while (largest != p);
}

/**
 * @brief loop version of min_heapify, should be faster
 * @see min_heapify().
 */
static void min_heapify_loop (Heap *h, int i)
{
	int l, r, minimum;
	int tmp = i;
	int p;

	do {
		p = tmp;
		l = HEAP_LEFT_INDEX (tmp);
		r = HEAP_RIGHT_INDEX (tmp);

		if ((l < h->card) && (h->data[l] < h->data[tmp]))
		{
			minimum = l;
		}
		else
		{
			minimum = tmp;
		}

		if ((r < h->card) && (h->data[r] < h->data[minimum]))
		{
			minimum = r;
		}

		if (minimum != tmp)
		{
			swap (&(h->data[minimum]), &(h->data[tmp]));
			tmp = minimum;
		}
	} while (p != minimum);
}

static Heap *heap_new_from_array (HeapType heap_type, int *array, int size)
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
	h->growing_factor = 0;
	h->size = size;
	h->type = heap_type;
	h->heapify_func = (heap_type == MAX_HEAP) ? max_heapify : min_heapify;

	h->card = size;
	for (i = HEAP_PARENT_INDEX (h->card); i >= 0; i--)
	{
		h->heapify_func (h, i);
	}
	
	return h;
}
