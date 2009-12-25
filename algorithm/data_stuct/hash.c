#include <stdlib.h>
#include <assert.h>
#include "hash.h"
#include "list.h"

typedef int (*hash_func_t) (int key, int size);

#define MULTI_HASH_FACTOR 0.6180339887

int divide_hash (int key, int size);
int multi_hash (int key, int size);


struct _hash
{
	List **lists;
	int list_size;
	int card;
	int growing_factor;
	key_func_t key_f;
	compare_func_t cmp_f;
	hash_func_t hash_f;
};

Hash *hash_new (int list_size, key_func_t key_f, compare_func_t cmp_f)
{
	Hash *h;
	int i, j;

	assert (list_size > 0);
	assert (key_f != NULL);

	h = (Hash *)Malloc (sizeof(Hash));
	if (h == NULL)
	{
		return NULL;
	}

	h->lists = (List **)Malloc (sizeof (List *) * list_size);
	if (h->lists == NULL)
	{
		free (h);
		return NULL;
	}

	for (i = 0; i < list_size; i++)
	{
		h->lists[i] = list_new (cmp_f);

		if (h->lists[i] == NULL)
		{
			for (j = 0; j < i; j++)
			{
				list_free (h->lists[j]);
			}

			free (h);
			return NULL;
		}
	}

	h->list_size = list_size;
	h->card = 0;
	h->growing_factor = 10;
	h->key_f = key_f;
	h->cmp_f = cmp_f;
	h->hash_f = divide_hash;

	return h;
}

void key_free (Hash *h)
{
	int i;

	assert (h != NULL);

	key_flush (h);
	
	for (i = 0; i < (h->list_size); i++)
	{
		list_free (h->lists[i]);
	}

	free (h->lists);
	free (h);
}

void key_flush (Hash *h)
{
	int i;

	assert (h != NULL);

	for (i = 0; i < (h->list_size); i++)
	{
		list_flush (h->lists[i]);
	}

	h->card = 0;
}

bool hash_is_empty (const Hash *h)
{
	assert (h != NULL);
	return (h->card == 0);
}

int hash_get_card (const Hash *h)
{
	assert (h != NULL);
	return h->card;
}

int hash_get_growing_factor (const Hash *h)
{
	assert (h != NULL);
	return h->growing_factor;
}

void hash_set_growing_factor (Hash *h, int value)
{
	assert (h != NULL);
	h->growing_factor = value;
}

void hash_set_compare_func (Hash *h, compare_func_t cmp_f)
{
	assert (h != NULL);
	h->cmp_f = cmp_f;
}

void hash_insert (Hash *h, void *data)
{
	int key;
	void *found;

	assert (h != NULL);

	key = h->hash_f (h->key_f (data), h->list_size);

	if ((found = list_search (h->lists[key], data)) == NULL)
	{
		list_insert_head (h->lists[key], data);
		(h->card)++;
	}
	else
	{
		printf ("elements already in hash table\n");
	}

	return;
}

void *hash_search (const Hash *h, void *data)
{
	int key;

	assert (h != NULL);
	
	key = h->hash_f (h->key_f (data), h->list_size);

	return list_search (h->lists[key], data);
}

void *hash_delete (Hash *h, void *data)
{
	int key;
	void *rst;

	assert (h != NULL);

	key = h->hash_f (h->key_f (data), h->list_size);

	rst = list_delete (h->lists[key], data);

	if (rst != NULL)
	{
		(h->card)--;
	}

	return rst;
}

void hash_dump (const Hash *h, FILE *file, write_func_t f)
{
	int i;

	assert (h != NULL);

	fprintf (file, "<HASH REF=\"%p\" LIST_SIZE=\"%d\" CARD=\"%d\" GROWING_FACTOR=\"%d\">",
			(void *)h, h->list_size, h->card, h->growing_factor);
	for (i = 0; i < h->list_size; i++)
	{
		list_dump (h->lists[i], file, f);
	}
	fprintf (file, "</HASH>\n");
}

void key_foreach (Hash *h, foreach_func_t f, void *data)
{
	int i;

	assert (h != NULL);

	for (i = 0; i < h->list_size; i++)
	{
		list_foreach (h->lists[i], f, data);
	}
}

int sum_key (void *data, int len)
{
	int i;
	int val = 0;

	assert (data != NULL);

	char *ptr = (char *)data;
	for (i = 0; i < len; i++)
	{
		val += (*ptr);
	}

	return val;
}

int divide_hash (int key, int size)
{
	return (key % size);
}

int multi_hash (int key, int size)
{
	double d;

	d = (double)key;
	d *= MULTI_HASH_FACTOR;
	d -= (int)d;
	
	return (int)(size * d);
}
