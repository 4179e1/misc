#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "_idsl_node.h"
#include "_idsl_list.h"
#include "idsl_types.h"
#include "idsl_list.h"

struct _idsl_list {
	_idsl_node_t d;			/* begin of the list (sentinel)     */
	_idsl_node_t z;			/* end of the list (sentinel)       */
	char*	name;
	ulong card;

	idsl_alloc_func_t alloc_func;
	idsl_free_func_t free_func
};

struct _idsl_list_cursor {
	_idsl_node_t c;
	idsl_list_t l;
};

static idsl_element_t
default_alloc (void* e);

static void
default_free (idsl_element_t e);

static _idsl_node_t
search_by_function (idsl_list_t l, idsl_compare_func_t comp_f, const void* v);

static _idsl_node_t
search_by_position (idsl_list_t l, ulong pos);

static idsl_element_t
update_cursor (idsl_list_cursor_t c);

static _idsl_node_t
sort (_idsl_node_t u, idsl_compare_func_t comp_f, _idsl_node_t z);

static _idsl_node_t
merge (_idsl_node_t s, _idsl_node_t t, idsl_compare_func_t comp_f, idsl_node_t z);

static idsl_location_t
get_location (idsl_list_t list, _idsl_node_t node);


idsl_list_t
idsl_list_alloc (const char* name, idsl_alloc_func_t alloc_func, idsl_free_func_t free_func) {
	idsl_list_t list;

	list = (idsl_list_t) malloc (sizeof (struct _idsl_list));
	if (list == NULL) {
		return NULL;
	}

	list->d = _idsl_node_alloc();
	if (list->d == NULL) {
		free (list);
		return NULL;
	}

	list->z = _idsl_node_alloc();
	if (list->z == NULL) {
		_idsl_node_free (list->d);
		free (list);
		return NULL;
	}

	_idsl_node_link (list->d, list->z);
	_idsl_node_set_succ (list->z, list->d);
	_idsl_node_set_pred (list->d, list->z);

	list->card = 0UL;
	list->alloc_func = alloc_func ? alloc_func : default_alloc;
	list->free_func = free_func ? free_func : default_free;

	return list;
}
	
		
