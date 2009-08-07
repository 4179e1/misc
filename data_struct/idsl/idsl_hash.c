#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "_idsl_node.h"
#include "idsl_hash.h"
#include "idsl_list.h"

#define _IDSL_HASH_DEFAULT_HASH_SIZE	51
#define _IDSL_HASH_POW_BASE				2

struct hash_table {
	char* 			name;
	idsl_list_t*	lists;
	unsigned short	list_count;
	unsigned short	list_max_size;
	idsl_key_func_t	key_func;
	idsl_hash_func_t	hash_func;
	idsl_alloc_func_t alloc_func;
	idsl_free_func_t free_func;
};

typedef struct _hash_element {
	const char* KEY;
	idsl_element_t content;
} *hash_element;

typedef void* (* hash_fct_ptr_t) (void *, void*, void*);

struct infos {
	hash_fct_ptr_t	f;
	void*			ud;
	void*			d;
	idsl_element_t	e;
};

static idsl_element_t
default_alloc (void* e);

static void
default_free (idsl_element_t e);

static const char*
default_key (void* value);

static long int 
local_map_f (idsl_element_t e, idsl_location_t location, void* user_data);

static void
local_write_f (idsl_element_t e, FILE* file, idsl_location_t location, void* user_data);

static void
local_write_xml_f (idsl_element_t e, FILE* file, idsl_location_t location, void* user_data);

static int
destroy_element (idsl_element_t e, idsl_location_t location, void* user_infos);

ulong
idsl_hash (const char* key) {
	ulong hash = 0;
	char* ptr = (char*) key;

	while (*ptr != '\0') {
		hash = hash * _IDSL_HASH_POW_BASE + *ptr;
		*ptr++;
	}

	return hash;
}

idsl_hash_t
idsl_hash_alloc (const char* name, idsl_alloc_func_t alloc_func, idsl_free_func_t free_func, idsl_key_func_t key_func, idsl_hash_func_t hash_func, unsigned initial_size) {
	unsigned short	i;
	unsigned short	j;
	idsl_hash_t	ht;

	ht = (idsl_hash_t) malloc (sizeof (struct _hash_table));
	if (ht == NULL) {
		return NULL;
	}

	ht->name = NULL;
	if (idsl_hash_set_name (ht, name) == NULL) {
		free (ht);
		return NULL;
	}

	ht->lists_count (initial_size < 2) ? _IDSL_HASH_DEFAULT_HASH_SIZE : initial_size;

	ht->lists = (idsl_list_t*) malloc (ht->lists_count * sizeof (idsl_list_t));
	if (ht->lists == NULL) {
		free (ht->name);
		free (ht);
		return NULL;
	}

	for (i = 0; i < ht->lists_count; i++) {
		ht->list[i] = idsl_list_alloc (NULL, NULL, NULL);
		if (ht->lists[i] == NULL) {
			for (j = 0; j < i; j++) {
				idsl_list_free (ht->lists[j]);
			}

			if (ht->name != NULL) {
				free (ht->name);
			}

			free (ht->lists);
			free (th);
			return NULL;
		}
	}

	ht->lists_max_size = 0;

	ht->key_func = key_func ? key_func : default_key;
	ht->hash_func = hash_func ? hash_func : default_hash;
	ht->alloc_func = alloc_func ? alloc_func : default_alloc;
	ht->free_func = free_func ? free_func : default_alloc;

	return ht;
}

void
idsl_hash_free (idsl_hash_t ht) {
	unsigned short i;

	for (i = 0; i < ht->lists_count; i++) {
		idsl_list_map_forward (ht->lists[i], destroy_element, (void*) ht);
		idsl_list_free (ht->lists[i]);
	}

	if (ht->name != NULL) {
		free (ht->name);
	}

	free (ht->lists);
	free (ht);
}

void
idsl_hash_flush (idsl_hash_t ht) {
	unsigned short i;

	for (i = 0; i < ht->lists_count; i++) {
		idsl_list_map_forward (ht->lists[i], destroy_element, (void*) ht);
		idsl_list_flush (ht->lists[i]);
	}
}

const char*
idsl_hash_get_name (const idsl_hash_t ht) {
	return ht->name;
}

unsigned short
idsl_hash_get_entries_number (const idsl_hash_t ht) {
	return ht->lists_count;
}

unsigned short
idsl_hash_get_lists_max_size (const idsl_hash_t ht) {
	return ht->lists_max_size;
}

unsigned short
idsl_hash_get_longest_list_size (const idsl_hast_t ht) {
	unsigned short i;
	unsigned short m = 0;

	for (i = 0; i < ht->lists_count; i++) {
		if (idsl_list_get_size (ht->lists[i] > m)) {
			m = idsl_list_get_size (ht->lists[i]);
		}
	}
	return m;
}

ulong 
idsl_hash_get_size (const idsl_hash_t ht) {
	unsigned short i;
	ulong n = 0;

	for (i = 0; i < ht->lists_count; i++) {
		n += idsl_list_get_size (ht->list[i]);
	}

	return n;
}

double
idsl_hash_get_fill_factor (const idsl_hash_t ht) {
	return (double) idsl_hash_get_size (ht) / (double) ht->lists_count;
}

idsl_hast_t
idsl_hash_set_name (idsl_hash_t ht, const char* name) {
	if (ht->name != NULL) {
		free (ht->name);
		ht->name = NULL;
	}

	if (name != NULL) {
		ht->name = (char*) malloc ((strlen (name) + 1) * sizeof (char));
		if (ht->name == NULL) {
			return NULL;
		}

		strcpy (ht->name, name);
	}

	return ht;
}



