#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "hash.h"
#include "list.h"

#define MULTI_HASH_FACTOR 0.6180339887

#define HASH_POWER_BASE 2


#ifdef _USE_DIVIDE
static int index_by_divide (int hash_value, int size);
#define INDEX_FUNC(V, S) (index_by_divide((V), (S)))
#else
static int index_by_multi (int hash_value, int size);
#define INDEX_FUNC(V, S) (index_by_multi((V), (S)))
#endif /* _USE_DIVIDE */

static int search_by_key (const void *data, const void *key);

static int default_hash (const char *key);

static void hash_dump_func (const void *elem, FILE *file, void *data);
static bool hash_foreach_func (void *elem, void *data);

struct _hash
{
	List **lists;
	int list_size;
	int card;
	int growing_factor;
	hash_func_t hash_f;
};

typedef struct _hash_element
{
	char *key;
	void *data;
} HashElement;

typedef struct _hash_info
{
	write_func_t write_f;
	foreach_func_t f; 
	void *data;
} HashInfo;

Hash *hash_new (int list_size, hash_func_t hash_f)
{
	Hash *h;
	int i, j;

	assert (list_size > 0);

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
	h->hash_f = hash_f ? hash_f : default_hash;

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


void *hash_insert (Hash *h, const char *key, void *data)
{
	int index;
	int len;
	HashElement *e;

	assert (h != NULL);

	e = (HashElement *)Malloc (sizeof (HashElement));
	if (e == NULL)
	{
		return NULL;
	}

	len = strlen (key);
	e->key = (void *)Malloc ((len + 1) * sizeof (char));
	strncpy (e->key, key, len + 1);
	if (e->key == NULL)
	{
		free (e);
		return NULL;
	}
	e->data = data;

	index = INDEX_FUNC (h->hash_f (e->key), h->list_size);

	list_insert_head (h->lists[index], e);
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
	free (elem->key);
	free (elem);
	(h->card)--;
	return data;
}

void hash_dump (const Hash *h, FILE *file, write_func_t f, void *data)
{
	int i;
	HashInfo info;

	assert (h != NULL);

	info.data = data;
	info.write_f = f;

	fprintf (file, "<HASH REF=\"%p\" LIST_SIZE=\"%d\" CARD=\"%d\" GROWING_FACTOR=\"%d\">",
			(void *)h, h->list_size, h->card, h->growing_factor);
	for (i = 0; i < h->list_size; i++)
	{
		list_dump (h->lists[i], file, hash_dump_func, &info);
	}
	fprintf (file, "</HASH>\n");
}


void hash_foreach (Hash *h, foreach_func_t f, void *data)
{
	int i;
	HashInfo info;

	assert (h != NULL);
	assert (f != NULL);

	info.data = data;
	info.f = f;

	for (i = 0; i < h->list_size; i++)
	{
		list_foreach (h->lists[i], hash_foreach_func, &info);
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
	if (i->f)
	{
		return i->f (e->data, i->data);
	}
	return false;
}

static void hash_dump_func (const void *elem, FILE *file, void *data)
{
	HashInfo *i = (HashInfo *)data;
	i->write_f (elem, file, i->data);
}

static int default_hash (const char *key)
{
	int val = 0;
	const char *ptr = key;

	while (*ptr != '\0')
	{
		val = val * HASH_POWER_BASE + (*ptr);
		ptr++;
	}

	return val;
}

#ifdef _USE_DIVIDE
static int index_by_divide (int hash_value, int size)
{
	return (hash_value % size);
}
#endif /* _USE_DIVIDE */

static int index_by_multi (int hash_value, int size)
{
	double d;

	d = (double)hash_value;
	d *= MULTI_HASH_FACTOR;
	d -= (int)d;
	
	return (int)(size * d);
}
