#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"
#include "base.h"

static int prev (int cur, int size);
static int next (int cur, int size);

struct _queue
{
	void **data;
	int head;
	int tail;
	int size;
	int card;
	int growing_factor;
};

Queue *queue_new(int size)
{
	Queue *q;
	q = (Queue *)Malloc (sizeof (Queue));
	if (q == NULL)
	{
		return NULL;
	}

	q->data = (void **)Malloc (sizeof (void*) * size);
	if (q->data == NULL)
	{
		free (q);
		return NULL;
	}

	q->tail = 0;
	q->head = 0;
	q->size = size;
	q->card = 0;
	q->growing_factor = 10;

	return q;
}

void queue_free (Queue *q)
{
	assert (q != NULL);
	free (q->data);
	free (q);
}

void queue_flush (Queue *q)
{
	assert (q != NULL);
	q->head = 0;
	q->tail = 0;
	q->card = 0;
}

bool queue_is_empty (const Queue *q)
{
	assert (q != NULL);
	return (q->card == 0);
}

int queue_get_size (const Queue *q)
{
	assert (q != NULL);
	return q->size;
}

int queue_get_card (const Queue *q)
{
	assert (q != NULL);
	return q->card;
}

int queue_get_growing_factor (const Queue *q)
{
	assert (q != NULL);
	return q->growing_factor;
}

void queue_set_growing_factor (Queue *q, int value)
{
	assert (q != NULL);
	q->growing_factor = value;
}

void queue_push_head (Queue *q, const void *data)
{
	assert (q != NULL);
	(q->card)++;
	if ((q->card) == (q->size))
	{
		int i, cur;
		void **tmp;
		(q->card)--;
		tmp = (void **)Malloc (sizeof(void *) * ((q->size) + (q->growing_factor)));
		if (tmp == NULL)
		{
			return;
		}
		for (i = 0, cur = q->head; i < q->card; i++, cur = next (cur, q->size))
		{
			tmp[i] = q->data[cur];
		}
		free (q->data);
		q->data = tmp;
		q->head = 0;
		q->tail = q->card;
		q->size += q->growing_factor;
		(q->card)++;
	}
	q->head = prev (q->head, q->size);
	q->data[q->head] = data;
}

void queue_push_tail (Queue *q, const void *data)
{
	assert (q != NULL);
	(q->card++);
	if ((q->card) == (q->size))
	{
		int i, cur;
		void **tmp;
		(q->card)--;
		tmp = (void **)Malloc (sizeof(void *) * ((q->size) + (q->growing_factor)));
		if (tmp == NULL)
		{
			return;
		}
		for (i = 0, cur = q->head; i < q->card; i++, cur = next (cur, q->size))
		{
			tmp[i] = q->data[cur];
		}
		free (q->data);
		q->data = tmp;
		q->head = 0;
		q->tail = q->card;
		q->size += q->growing_factor;
		(q->card)++;
	}
	q->data[q->tail] = data;
	q->tail = next (q->tail, q->size);
}

void *queue_head (const Queue *q)
{
	assert (q != NULL);
	return q->data[q->head];
}

void *queue_tail (const Queue *q)
{
	assert (q != NULL);
	return q->data[next (q->tail, q->size)];
}

void *queue_pop_head (Queue *q)
{
	void *tmp;

	assert (q != NULL);
	tmp = q->data[q->head];
	q->head = next (q->head, q->size);
	(q->card)--;
	return tmp;
}

void *queue_pop_tail (Queue *q)
{
	assert (q != NULL);
	q->tail = prev (q->tail, q->size);
	(q->card)--;
	return q->data[q->tail];
}

void queue_dump (const Queue *q, FILE *file, write_func_t f)
{
	int i, cur;
	assert (q != NULL);
	fprintf (file, "<QUEUE HEAD=\"%d\" TAIL=\"%d\" CARD=\"%d\" SIZE=\"%d\" GROWING_FACTOR=\"%d\">", q->head, q->tail, q->card, q->size, q->growing_factor);
	for (i = 0, cur = q->head; i < q->card; i++, cur = next (cur, q->size))
	{
		fprintf (file, "<NODE CONTENT=\"%p\" CUR=\"%d\">", q->data[cur], cur);
		if (f)
		{
			f(q->data[cur], file);
		}
		fprintf (file, "</NODE>");
	}
	fprintf (file, "</QUEUE>\n");
}

void queue_foreach (Queue *q, foreach_func_t f, void *data)
{
	int i, cur;

	assert (q != NULL);
	for (i = 0, cur = q->head; i < q->card; i++, cur = next (cur, q->size))
	{
		if (f(q->data[cur], data) == false)
		{
			break;
		}
	}
}

/**
 * private func 
 */
static int next (int cur, int size)
{
	return ((cur + 1) % size);
}

static int prev (int cur, int size)
{
	return ((cur + size - 1) % size);
}
