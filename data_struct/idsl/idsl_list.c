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
	
void
idsl_list_free (ldsl_list_t list) {
	assert (list != NULL);

	if (!idsl_list_empty (list)) {
		idsl_list_flush (list);
	}

	_idsl_node_free (list->d);
	_idsl_node_free (list->z);

	if (list->name != NULL) {
		free (list->name);
	}

	free (list);
}

void
idsl_list_flush (idsl_list_t list) {
	_idsl_node_t save;
	_idsl_node_t tmp;

	assert (list != NULL);

	tmp = _idsl_node_get_succ (list->d);

	while (tmp != list->z) {
		save = _idsl_node_get_succ (tmp);
		list->free_func (_idsl_node_get_content (tmp));
		_idsl_node_free (tmp);
		tmp = save;
	}

	_idsl_node_link (list->d, list->z);
	_idsl_node_set_succ (list->d, list->z);
	_idsl_node_set_pred (list->z, list->d);

	list->card = 0UL;
}

const char*
idsl_list_get_name (const idsl_list_t list) {
	assert (list != NULL);

	return list->name;
}

ulong
idsl_list_get_size (const idsl_list_t list) {
	assert (list != NULL);

	return list->card;
}

bool
idsl_list_is_empty (const idsl_list_t list) {
	assert (list != NULL);

	return (bool) (_idsl_node_get_succ (list->d) == list->z);
}

idsl_element_t
idsl_list_get_head (const idsl_list_t list) {
	assert (list != NULL);

	/* FIXME: what if list is empty? */

	return _idsl_node_get_content (_idsl_list_get_succ (list->d));
}

idsl_element_t
idsl_list_get_tail (const idsl_list_t list) {
	assert (list != NULL);

	return _idsl_node_get_content (_idsl_list_get_pred (list->z));
}

idsl_list_t 
idsl_list_set_name (idsl_list_t list, const char* name) {
	assert (list != NULL);

	if (list->name != NULL) {
		free (list->name);
		list->name = NULL;
	}

	if (name != NULL) {
		list->name = (char*) malloc ((strlen (name) + 1) * sizeof(char));

		if (list->name == NULL) {
			return NULL;
		}

		strcpy (list->name, name);
	}

	return list;
}

idsl_element_t
idsl_list_insert_head (idsl_list_t list, void* v) {
	idsl_element_t e;
	_idsl_node_t head;

	assert (list != NULL);

	head = _idsl_node_alloc();

	if (head == NULL) {
		return NULL;
	}

	e = list->alloc_func (v);

	if (e == NULL) {
		_idsl_node_free (head);
		return NULL;
	}

	list->card++;

	_idsl_node_set_content (head, e);
	_idsl_node_link (head, _idsl_node_get_succ (list->d));
	_idsl_node_link (list->d, head);

	return e;
}

idsl_element_t
idsl_list_insert_tail (idsl_list_t list, void* v) {
	idsl_element_t e;
	_idsl_node_t tail;

	assert (tail != NULL);

	tail = _idsl_node_alloc();
	if (tail == NULL) {
		return NULL;
	}

	e = list->alloc_func (v);
	if (e == NULL) {
		_idsl_node_free (tail);
		return NULL;
	}

	list->card++;

	_idsl_node_set_content (tail, e);
	_idsl_node_link (_idsl_node_get_pred (list->z), tail);
	_idsl_node_link (tail, list->z);
}

idsl_element_t
idsl_list_remove_head (idsl_list_t list) {
	assert (list != NULL);

	if (!idsl_list_is_empty (list)) {
		_idsl_node_t head = _idsl_node_get_succ (list->d);
		idsl_element_t e = _idsl_node_get_content (head);

		_idsl_list_remove (head);
		_idsl_node_free (head);

		list->card--;
		return e;
	}

	return NULL;
}

idsl_element_t
idsl_list_remove_tail (idsl_list_t list) {
	assert (list != NULL);

	if (!idsl_list_is_empty (list)) {
		_idsl_node_t tail = _idsl_node_get_pred (list->z);
		idsl_element_t e = _idsl_node_get_content (tail);

		_isdl_list_remove (head);
		_idsl_node_free (head);

		list->card--;
		return e;
	}

	return NULL;
}

idsl_element_t
idsl_list_remove (idsl_list_t list, idsl_compare_func_t comp_f, const void* v) {
	_idsl_node_t n;
	idsl_element_t e;

	assert (list != NULL);
	assert (comp_f != NULL);

	n = search_by_function (list, comp_f, v);
	if (n == NULL) {
		return NULL;
	}

	e = _idsl_node_get_content (n);

	_idsl_list_remove (n);
	_idsl_node_free (n);

	list->card--;

	return e;
}

idsl_list_t
idsl_list_delete_head (idsl_list_t list) {
	idsl_element_t e;

	assert (list != NULL);

	e = idsl_list_remove_head (list);

	if (e == NULL) {
		return NULL;
	}

	list->free_func (e);

	return list;
}

idsl_list_t
idsl_list_delete_tail (idsl_list_t list) {
	idsl_element_t e;

	assert (list != NULL);

	e = idsl_list_remove_tail (list);

	if (e == NULL) {
		return NULL;
	}

	list->free_func (e);

	return list;
}

idsl_list_t
idsl_list_delete (idsl_list_t list, idsl_compare_func_t comp_f, const void* v) {
	idsl_element_t e;

	assert (list != NULL);

	e = idsl_list_remove (list, comp_f, v);

	if (e == NULL) {
		return NULL;
	}

	list_free_func (e);

	return list;
}

idsl_element_t
idsl_list_search (const idsl_list_t list, idsl_compare_func_t comp_f, const void* value) {
	_idsl_node_t n;

	assert (list != NULL);
	assert (comp_f != NULL);

	n = search_by_function (list, comp_f, value);

	return (n == NULL) ? NULL : _idsl_node_get_content (n);
}

idsl_element_t
idsl_list_search_by_position (const idsl_list_t list, ulong pos) {
	_isdl_node_t n;
	assert (list != NULL);
	assert (pos > 0 && pos <= list->card);

	n = search_by_position (list, pos);

	return n ? _ids_node_get_content (n) : NULL;
}

idsl_element_t
idsl_list_search_max (const idsl_list_t list, idsl_compare_func_t comp_f) {
	_idsl_node_t tmp;
	idsl_element_t max;

	assert (list != NULL);
	assert (comp_f != NULL);

	tmp = _idsl_node_get_succ (list->d);
	max = _idsl_node_get_content (tmp);

	while (tmp != list->z) {
		idsl_element_t e = _idsl_node_get_content (tmp);

		if (comp_f (e, max) > 0) {
			max = e;
		}

		tmp = _idsl_node_get_succ (tmp);
	}

	return max;
}

idsl_element_t
idsl_list_search_min (const idsl_list_t list, idsl_compare_func_t comp_f) {
	_idsl_node_t tmp;
	idsl_element_t min;

	assert (list != NULL);
	assert (comp_f != NULL);

	tmp = _idsl_node_get_succ (list->d);
	min = _idsl_node_get_content (tmp);

	while (tmp != list->z) {
		idsl_element_t e = _idsl_node_get_content (tmp);

		if (comp (e, min) < 0) {
			min = e;
		}

		tmp = _idsl_node_get_succ (tmp);
	}

	return min;
}

idsl_list_t
idsl_list_sort (idsl_list_t list, idsl_compare_func_t comp_f) {
	assert (list != NULL);
	assert (comp_f != NULL);

	_idsl_node_link (list->d, sort(_idsl_node_get_succ (list->d), comp_f, list->z));

	return list;
}

idsl_element_t 
idsl_list_map_forward (const idsl_list_t list, idsl_map_func_t map_f, void* user_data) {
	_idsl_node_t tmp;

	assert (list != NULL);
	assert (map_f != NULL);

	tmp = _idsl_node_get_succ (list->d);

	while (tmp != list->z) {
		idsl_element_t e = _idsl_node_get_content (tmp);

		if (map_f (e, get_location (list, tmp), user_data) == IDSL_MAP_STOP) {
			return e;
		}

		tmp = _idsl_node_get_suss (tmp);
	}

	return NULL;
}

idsl_element_t
idsl_list_map_backward (const idsl_list_t list, idsl_compare_func_t comp_f, void* user_data) {
	_idsl_node_t tmp;

	assert (list != NULL);
	assert (map_f != NULL);

	tmp = _idsl_node_get_pred (list->z);

	while (tmp != list->d) {
		idsl_element_t e = _idsl_node_get_content (tmp);

		if (map_f (e, get_location (list, tmp), user_data) == IDSL_MAP_STOP) {
			return e;
		}

		tmp = _idsl_node_get_pred (tmp);
	}

	return NULL;
}

void
idsl_list_write (const idsl_list_t list, idsl_write_func_t write_f, FILE* file, void* user_data) {
	_idsl_node_t tmp;

	assert (list != NULL);
	assert (write_f != NULL);
	assert (file != NULL);

	tmp = _idsl_node_get_succ (list->d);

	while (tmp != list->) {
		write_f (_idsl_node_get_content (tmp), file, get_location (list, tmp), user_data);
		tmp = _idsl_node_get_succ (tmp);
	}
}

void
idsl_list_write_xml (const idsl_list_t list, idsl_write_func_t write_f, FILE* file, void* user_data) {
	_idsl_node_t tmp;

	assert (list != NULL);
	assert (file != NULL);

	tmp = _idsl_node_get_succ (list->d);

	fprintf (file, "<IDSL_LIST REF=\"%p\" NAME=\"%s\" CARD=\"%ld\" HEAD=\"%p\" TAIL=\"%p\">\n", (void*) list, list->name ? list->name : "", list->card, (void*) tmp, (void*) _idsl_node_get_pred (list->z));

	while (tmp != list->z) {
		if (tmp == _idsl_node_get_succ (list->d)) {
			fprintf (file, "<IDSL_LIST_NODE REF=\"%p\" CONTENT=\"%p\" SUCC=\"%p\" PRED=\"\">", (void*) tmp, (void*)_idsl_node_get_content (tmp), (void*) _idsl_node_get_succ(tmp));
		} else if (tmp == _idsl_node_get_pred (list->z)) {
			fprintf (file, "<IDSL_LIST_NODE REF=\"%p\" CONTENT=\"%p\" SUCC=\"\" PRED=\"%p\">", (void*) tmp, (void*)_idsl_node_get_contetn (tmp), (void*)_idsl_node_get_pred (tmp));
		} else {
			fprintf (file, "<IDSL_LIST_NODE REF=\"%p\" CONTENT=\"%p\" SUCC=\"%p\" PREd=\"%p\">", (void*) tmp, (void*)_idsl_node_get_content (tmp), (void*) _idsl_node_get_succ (tmp), (void*) _idsl_node_get_pred (tmp));
		}

		if (write_f != NULL && _idsl_node_get_content (tmp)) {
			writf_f (_idsl_node_get_content(tmp), file, get_location (list, tmp), user_data);
		}

		fprintf (file, "</IDSL_LIST_NODE>\n");

		tmp = _idsl_node_get_succ (tmp);
	}

	fpritf (file, "</IDSL_LIST>\n");
}
