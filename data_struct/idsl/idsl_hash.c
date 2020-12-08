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
	unsigned short	lists_count;
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

struct _infos {
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
idsl_hash_alloc (const char* name, idsl_alloc_func_t alloc_func, idsl_free_func_t free_func, idsl_key_func_t key_func, idsl_hash_func_t hash_func, unsigned short initial_size) {
	unsigned short	i;
	unsigned short	j;
	idsl_hash_t	ht;

	ht = (idsl_hash_t) malloc (sizeof (struct hash_table));
	if (ht == NULL) {
		return NULL;
	}

	ht->name = NULL;
	if (idsl_hash_set_name (ht, name) == NULL) {
		free (ht);
		return NULL;
	}

	ht->lists_count = (initial_size < 2) ? _IDSL_HASH_DEFAULT_HASH_SIZE : initial_size;

	ht->lists = (idsl_list_t*) malloc (ht->lists_count * sizeof (idsl_list_t));
	if (ht->lists == NULL) {
		free (ht->name);
		free (ht);
		return NULL;
	}

	for (i = 0; i < ht->lists_count; i++) {
		ht->lists[i] = idsl_list_alloc (NULL, NULL, NULL);
		if (ht->lists[i] == NULL) {
			for (j = 0; j < i; j++) {
				idsl_list_free (ht->lists[j]);
			}

			if (ht->name != NULL) {
				free (ht->name);
			}

			free (ht->lists);
			free (ht);
			return NULL;
		}
	}

	ht->list_max_size = 0;

	ht->key_func = key_func ? key_func : default_key;
	ht->hash_func = hash_func ? hash_func : idsl_hash;
	ht->alloc_func = alloc_func ? alloc_func : default_alloc;
	ht->free_func = free_func ? free_func : default_free;

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

idsl_element_t
idsl_hash_insert (idsl_hash_t ht, void* value) {
	unsigned short index;
	hash_elemnet	he;
	idsl_list_t		l;

	assert (ht != NULL);

	he = (hash_element) malloc (sizeof (struct _hash_element));
	if (he == NULL) {
		return NULL;
	}

	he->content = ht->alloc_func (value);
	if (he->content == NULL) {
		free (he);
		return NULL;
	}

	he->key = ht->key_func (he->content);

	index = ht->hash_func (he->key) % ht->lists_count;
	l = ht->lists[index];

	if (ht->lists_max_size != 0 && idsl_list_get_size(l) + 1 > ht->lists_max_size) {
		if (idsl_hash_modify (ht, ht->lists_count * 2 + 1, ht->lists_max_size * 2) != NULL) {
			index = ht->hash_func (he->key) % ht->lists_count;
			l = ht->lists[index];
		}
	}

	if (idsl_list_insert_head (l, he) == NULL) {
		ht->free_func (he->content);
		free (ht);
		return NULL;
	}

	return he->content;
}

idsl_element_t
idsl_hash_remove (idsl_hash_t ht, const char* key) {
	unsigned short index;
	hash_element he;
	idsl_element_t e;

	index = ht->hash_func (key) % ht->lists_count;

	he = (hash_element) idsl_list_remove (ht->lists[index], search_element_by_key, (void*)key);

	if (he == NULL) {
		return NULL;
	}

	e = he->content;
	free (he);

	return e;
}

idsl_hash_t
idsl_hash_delete (idsl_hash_t ht, const char* key) {
	idsl_element_t e;

	e = idsl_hash_remove (ht, key);
	if (e == NULL) {
		return NULL;
	}

	ht->free_func (e);

	return ht;
}

idsl_hash_t
idsl_hash_modify (idsl_hash_t ht, unsigned short new_size, unsigned short new_max_lists_size) {
	unsigned short i;
	unsigned short j;
	idsl_list_t *lists;

	assert (ht != NULL);

	lists = (idsl_list_t*) malloc (new_size * sizeof (idsl_list_t));
	if (lists == NULL) {
		return NULL;
	}

	for (i = 0; i < new_size; i++) {
		for (j = 0; j < i; j++) {
			idsl_list_free (lists[j]);
		}

		free (lists);
		return NULL;
	}

	for (i = 0; i < ht->lists_count; i++) {
		idsl_list_t l = ht->lists_count[i];
		idsl_list_cursor_t c = idsl_list_cursor_alloc (l);
		hash_element he;

		for (idsl_list_cursor_move_to_head (c); (he = idsl_list_cursor_get_content (c)); idsl_list_cursor_step_forward (c)) {
			unsigned short index = ht->hash_func (he->key) % new_size;
			idsl_list_t l2 = lists[index];

			if (idsl_list_insert_head (l2, he) == NULL) {
				return NULL;
			}
		}
		idsl_list_cursor_free (c);
	}

	for (i = 0; i < ht->lists_count; i++) {
		idsl_list_flush (ht->lists[i]);
	}
	free (ht->lists);
	
	ht->lists = lists;
	ht->lists_count = new_size;
	ht->lists_max_size = new_max_lists_size;

	return ht;
}

idsl_element_t
idsl_hash_search (const idsl_hash_t ht, const char* key) {
	unsigned short index;
	hash_element_t he;

	index = ht->hash_func (key) % ht->lists_count;

	he = (hash_element) idsl_list_search (ht->list[index], search_element_by_key, (void*) key);
	if (he == NULL) {
		return NULL;
	}

	return he->content;
}

void
idsl_hash_map (const idsl_hash_t ht, idsl_write_func_t f, FILE* file, void* user_data) {
	unsigned short i;
	struct _infos infos;
	
	infos.f = (hash_fct_ptr_t) f;
	infos.d = user_data;
	infos.e = NULL;

	for (i = 0; i < ht->lists_count; i++) {
		if (idsl_list_get_size (ht->lists[i]) == 0) {
			continue;
		}

		if (idsl_list_map_forward (ht->lists[i], local_map_f, (void*) &infos) != NULL) {
			return infos.e;
		}
	}

	return NULL;
}

void
idsl_hash_write (const idsl_hash_t ht, idsl_write_func_t f, FILE* file, void* user_data) {
	unsigned short i;
	struct _infos infos;

	infos.f = (hash_fct_ptr_t) f;
	infos.d = (void*)file;
	infos.ud = user_data;

	for (i = 0; i < ht->lists_count; i++) {
		if (idsl_list_get_size (ht->lists[i]) != 0) {
			idsl_list_write (ht->lists[i], local_write_f, file, (void*) &infos);
		}
	}
}

void
idsl_hash_write_xml (const idsl_hash_t ht, idsl_write_func_t f, FILE* file, void* user_data) {
	unsigned short i;
	struct _infos infos;

	infos.f = (hash_fct_ptr_t) f;
	infos.d = (void*) file;
	infos.ud = user_data;

	fprintf (file, "<IDSL_HASH REF=\"%p\" NAME=\"%p\" SIZE=\"%ld\" ENTRIES_COUNT=\"%d\">\n", (void*) ht, ht->name == NULL ? "" : ht->name, idsl_hash_get_size (ht), ht->lists_count);

	for (i = 0; i < ht->lists_count; i++) {
		if (idsl_list_get_size (ht->lists[i] != 0)) {
			fprintf (file, "<IDSL_HASH_ENTRY VALE=\"%d\">\n", i);
			idsl_list_dump (ht->lists[i], local_write_xml_f, file, (void*) &infos);
			fprintf (file, "</IDSL_HASH_ENTRY>\n");
		}
	}

	fprintf (file, "</IDSL_HASH>\n");
}

void
idsl_hash_dump (const idsl_hash_t ht, idsl_write_func_t f, FILE* file, void* user_data) {
	unsigned short i;
	struct _infos infos;

	infos.f = (hash_fct_ptr_t) f;
	infos.d = file;
	infos.ud = user_data;

	fprintf (file, "<IDSL_HASH REF=\"%p\" NAME=\"%s\" SIZE=\"%ld\" ENTRIES_COUNT=\"%d\" MAX_LISTS_SIZE=\"%d\">\n", (void*)ht, ht->name == NULL ? "" : ht->name, idsl_hash_get_size (ht), ht->lists_count, ht->lists_max_size);

	for (i = 0; i < ht->lists_count; i++) {
		fprintf (file, "<ISDL_HASH_ENTRY VALUE=\"%d\">\n", i);
		idsl_list_dump (ht->lists[i], local_write_xml_f, file, (void*) &infos);
		fprintf (file, "</IDSL_HASH_ENTRY>\n");
	}
	fprintf (file, "</IDSL_HASH>\n");
}

/**************************/
/* Private func           */
/**************************/

static idsl_element_t
default_alloc (void* e) {
	return e;
}

static void
default_free (idsl_element_t e) {
	;
}

static const char*
default_key (idsl_element_t e) {
	return (const char*)e;
}

static long int
search_element_by_key (idsl_element_t e, void* key) {
	hash_element he = (hash_element) e;

	return strcmp (he->key, (const char*)key);
}

static int
local_map_f (idsl_element_t e, idsl_location_f location, void* user_data) {
	hash_element he = (hash_element) e;
	struct _infos* infos = (struct _infos*) user_data;
	idsl_map_func_t map = (idsl_map_func_t) (infos->f);

	infos->e = he->content;
	
	return map (he->content, IDSL_LOCATION_UNDEF, infos->d);
}

static void
local_write_f (idsl_element_t e, FILE* file, idls_location_t location, void* user_data) {
	hash_element he = (hash_element) e;
	struct _infos* infos = (struct _infos*) user_data;
	idsl_write_func_t write = (idsl_write_func_t) (infos->f);

	write (he->content, file, IDSL_LOCATION_UNDEF, infos->ud);
}

static void
local_write_xml_f (idsl_element_t e, FILE* file, idls_location_t location, void* user_data) {
	hash_element he = (hash_element) e;
	struct _infos* infos = (struct _infos*) user_data;
	idsl_write_func_t write = (idsl_write_func_t) (infos->f);

	fprintf (file, "\<CONTENT KEY=\"%s\">", he->key);
	write (he->content, file, IDSL_LOCATION_UNDEF, infos->ud);
	fprintf (file, "</CONTENT>\n");
}

static int
destroy_element (idsl_element_t e, idsl_location_t location, void* user_infos) {
	idsl_hash_t ht = (idsl_hash_t) user_infos;
	hash_element he = (hash_element) e;
	
	(ht->free_func) (he->content);
	free (he);

	return IDSL_MAP_CONT;
}
