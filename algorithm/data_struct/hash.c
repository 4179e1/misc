#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "hash.h"
#include "list.h"

#define MULTI_HASH_FACTOR 0.6180339887

#define INDEX_FUNC(V, S) (index_by_multi((V), (S)))

int index_by_divide (int hash_value, int size);
int index_by_multi (int hash_value, int size);
static int search_by_key (const void *data, const void *key);
static bool hash_foreach_func (void *elem, void *data);

struct _hash
{
	List **lists;
	int list_size;
	int card;
	int growing_factor;
	key_func_t key_f;
	hash_func_t hash_f;
};

typedef struct _hash_element
{
	const char *key;
	void *data;
} HashElement;

typedef struct _hash_info
{
	foreach_func_t f; 
	void *data;
} HashInfo;

Hash *hash_new (int list_size, key_func_t key_f, hash_func_t hash_f)
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
		h->lists[i] = list_new ();

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
	h->hash_f = hash_f;

	return h;
}

void hash_free (Hash *h)
{
	int i;

	assert (h != NULL);

	hash_flush (h);
	
	for (i = 0; i < (h->list_size); i++)
	{
		list_free (h->lists[i]);
	}

	free (h->lists);
	free (h);
}

void hash_flush (Hash *h)
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


void *hash_insert (Hash *h, void *data)
{
	int index;
	HashElement *e;

	assert (h != NULL);

	e = (HashElement *)Malloc (sizeof (HashElement));
	if (e == NULL)
	{
		return NULL;
	}

	e->key = h->key_f (data);
	e->data = data;

	index = INDEX_FUNC (h->hash_f (e->key), h->list_size);

	list_insert_head (h->lists[index], data);
	(h->card)++;

	return data;
}

void *hash_search (const Hash *h, const char *key)
{
	int index;
	HashElement *elem;

	assert (h != NULL);
	
	index = INDEX_FUNC (h->hash_f (key), h->list_size);

	elem = list_search (h->lists[index], key, search_by_key);
	if (elem == NULL)
	{
		return NULL;
	}

	return elem->data;
}

void *hash_delete (Hash *h, const char *key)
{
	int index;
	HashElement *elem;
	void *data;

	assert (h != NULL);

	index = INDEX_FUNC (h->hash_f (key), h->list_size);

	elem = list_delete (h->lists[index], data, search_by_key);
	if (elem == NULL)
	{
		return NULL;
	}

	data = elem->data;
	free (elem);
	(h->card)--;
	return data;
}

void hash_dump (const Hash *h, FILE *file, write_func_t f)
{
	int i;

	assert (h != NULL);

	fprintf (file, "<HASH REF=\"%p\" LIST_SIZE=\"%d\" CARD=\"%d\" GROWING_FACTOR=\"%d\">",
			(void *)h, h->list_size, h->card, h->growing_factor);
	for (i = 0; i < h->list_size; i++)
	{
		//list_dump (h->lists[i], file, f);
	}
	fprintf (file, "</HASH>\n");
}


void hash_foreach (Hash *h, foreach_func_t f, void *data)
{
	int i;
	HashInfo *info;

	assert (h != NULL);
	assert (f != NULL);

	info = (HashInfo *)Malloc (sizeof (HashInfo));
	if (info == NULL)
	{
		return;
	}

	info->data = data;
	info->f = f;

	for (i = 0; i < h->list_size; i++)
	{
		list_foreach (h->lists[i], hash_foreach_func, info);
	}
}

/* compare_func_t */
static int search_by_key (const void *data, const void *key)
{
	HashElement *e = (HashElement *)data;
	return (strcmp (e->key, (const char *)key));
}

static bool hash_foreach_func (void *elem, void *data)
{
	HashElement *e = (HashElement *)elem;
	HashInfo *i = (HashInfo *)data;
	return i->f (e->data, i->data);
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

int index_by_divide (int hash_value, int size)
{
	return (hash_value % size);
}

int index_by_multi (int hash_value, int size)
{
	double d;

	d = (double)hash_value;
	d *= MULTI_HASH_FACTOR;
	d -= (int)d;
	
	return (int)(size * d);
}
