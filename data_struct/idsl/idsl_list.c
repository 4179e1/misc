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
	idsl_free_func_t free_func;
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
update_cursor (idsl_list_cursor_t c, _idsl_node_t n);

static _idsl_node_t
sort (_idsl_node_t u, idsl_compare_func_t comp_f, _idsl_node_t z);

static _idsl_node_t
merge (_idsl_node_t s, _idsl_node_t t, idsl_compare_func_t comp_f, _idsl_node_t z);

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
	_idsl_node_set_succ (list->z, list->z);
	_idsl_node_set_pred (list->d, list->d);

	list->card = 0UL;
	list->alloc_func = alloc_func ? alloc_func : default_alloc;
	list->free_func = free_func ? free_func : default_free;

	return list;
}

void
idsl_list_free (idsl_list_t list) {
	assert (list != NULL);

	if (!idsl_list_is_empty (list)) {
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

	return _idsl_node_get_content (_idsl_node_get_succ (list->d));
}

idsl_element_t
idsl_list_get_tail (const idsl_list_t list) {
	assert (list != NULL);

	return _idsl_node_get_content (_idsl_node_get_pred (list->z));
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

	return e;
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

		_idsl_list_remove (tail);
		_idsl_node_free (tail);

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

	list->free_func (e);

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
	_idsl_node_t n;
	assert (list != NULL);
	assert (pos > 0 && pos <= list->card);

	n = search_by_position (list, pos);

	return n ? _idsl_node_get_content (n) : NULL;
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

		if (comp_f (e, min) < 0) {
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

		tmp = _idsl_node_get_succ (tmp);
	}

	return NULL;
}

idsl_element_t
idsl_list_map_backward (const idsl_list_t list, idsl_map_func_t map_f, void* user_data) {
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

	while (tmp != list->z) {
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
			fprintf (file, "<IDSL_LIST_NODE REF=\"%p\" CONTENT=\"%p\" SUCC=\"\" PRED=\"%p\">", (void*) tmp, (void*)_idsl_node_get_content (tmp), (void*)_idsl_node_get_pred (tmp));
		} else {
			fprintf (file, "<IDSL_LIST_NODE REF=\"%p\" CONTENT=\"%p\" SUCC=\"%p\" PREd=\"%p\">", (void*) tmp, (void*)_idsl_node_get_content (tmp), (void*) _idsl_node_get_succ (tmp), (void*) _idsl_node_get_pred (tmp));
		}

		if (write_f != NULL && _idsl_node_get_content (tmp)) {
			write_f (_idsl_node_get_content(tmp), file, get_location (list, tmp), user_data);
		}

		fprintf (file, "</IDSL_LIST_NODE>\n");

		tmp = _idsl_node_get_succ (tmp);
	}

	fprintf (file, "</IDSL_LIST>\n");
}

void
idsl_list_dump (const idsl_list_t list, idsl_write_func_t write_f, FILE* file, void* user_data) {
	_idsl_node_t tmp;

	assert (list != NULL);
	assert (file != NULL);

	tmp = _idsl_node_get_succ (list->d);

	fprintf (file, "<IDSL_LIST REF=\"%p\" NAME=\"%s\" CARD=\"%ld\" HEAD=\"%p\" TAIL=\"%p\">\n", (void*) list, list->name ? list->name : "", list->card, (void*)list->d, (void*)list->z);

	if (_idsl_node_get_content (list->d)) {
		fprintf (file, "<IDSL_LIST_HEAD REF=\"%p\" CONTENT=\"%p\" SUCC=\"%p\" PRED=\"%p\"/>\n", (void*)list->d, (void*) _idsl_node_get_content (list->d), (void*) _idsl_node_get_succ(list->d), (void*) _idsl_node_get_pred (list->d));
	} else {
		fprintf (file, "<IDSL_LIST_HEAD REF=\"%p\" CONTENT=\"\" SUCC=\"%p\" PRED=\"%p\"/>\n", (void*)list->d, (void*) _idsl_node_get_succ (list->d), (void*) _idsl_node_get_pred (list->d));
	}

	while (tmp != list->z) {
		if (_idsl_node_get_content (tmp)) {
			fprintf (file, "<IDSL_LIST_NODE REF=\"%p\" CONTENT=\"%p\" SUCC=\"%p\" PRED=\"%p\">", (void*)tmp, (void*) _idsl_node_get_content (tmp), (void*) _idsl_node_get_succ (tmp), (void*) _idsl_node_get_pred(tmp));
		} else {
			fprintf (file, "<IDSL_LIST_NODE REF=\"%p\" CONTENT=\"\" SUCC=\"%p\" PRED=\"%p\">", (void*) tmp, (void*) _idsl_node_get_succ (tmp), (void*) _idsl_node_get_pred (tmp));
		}

		if (write_f != NULL) {
			write_f (_idsl_node_get_content (tmp), file, get_location (list, tmp), user_data);
		}

		fprintf (file, "</IDSL_LIST_NODE>\n");

		tmp = _idsl_node_get_succ (tmp);
	}

	if (_idsl_node_get_content (list->z)) {
		fprintf (file, "<IDSL_LIST_TAIL REF=\"%p\" CONTENT=\"%p\" SUCC=\"%p\" PRED=\"%p\"/>\n</IDSL_LIST>\n", (void*) list->z, (void*) _idsl_node_get_content (list->z), (void*)_idsl_node_get_succ (list->z), (void*)_idsl_node_get_pred (list->z));
	} else {
		fprintf (file, "<IDSL_LIST_TAIL REF=\"%p\" CONTENT=\"\" SUCC=\"%p\" PRED=\"%p\"/>\n<?IDSL_LIST>\n", (void*)list->z, (void*) _idsl_node_get_succ(list->z), (void*) _idsl_node_get_pred (list->z));
	}
}


idsl_list_cursor_t
idsl_list_cursor_alloc (const idsl_list_t list) {
	idsl_list_cursor_t c;

	assert (list != NULL);

	c = (idsl_list_cursor_t) malloc (sizeof (struct _idsl_list_cursor));

	if (c == NULL) {
		return NULL;
	}

	c->c = _idsl_node_get_succ (list->d);
	c->l = list;

	return c;
}

void
idsl_list_cursor_free (idsl_list_cursor_t c) {
	assert (c != NULL);

	free (c);
}

void
idsl_list_cursor_move_to_head (idsl_list_cursor_t c) {
	assert (c != NULL);

	c->c = _idsl_node_get_succ(c->l->d);
}

void
idsl_list_cursor_move_to_tail (idsl_list_cursor_t c) {
	assert (c != NULL);

	c->c = _idsl_node_get_pred (c->l->z);
}

idsl_element_t
idsl_list_cursor_move_to_value (idsl_list_cursor_t c, idsl_compare_func_t comp_f, void* v) {
	assert (c != NULL);
	assert (comp_f != NULL);

	return update_cursor (c, search_by_function (c->l, comp_f, v));
}

idsl_element_t
idsl_list_cursor_move_to_position (idsl_list_cursor_t c, ulong pos) {
	assert (c != NULL);
	assert (pos > 0 && pos <= c->l->card);

	return update_cursor (c, search_by_position (c->l, pos));
}

void
idsl_list_cursor_step_forward (idsl_list_cursor_t c) {
	assert (c != NULL);

	c->c = _idsl_node_get_succ (c->c);
}

void
idsl_list_cursor_step_backward (idsl_list_cursor_t c) {
	assert (c != NULL);

	c->c = _idsl_node_get_pred (c->c);
}

bool
idsl_list_cursor_is_on_head (const idsl_list_cursor_t c) {
	assert (c != NULL);

	if (idsl_list_is_empty (c->l)) {
		return FALSE;
	}

	return (bool) (c->c == _idsl_node_get_succ (c->l->d));
}

bool
idsl_list_cursor_is_on_tail (const idsl_list_cursor_t c) {
	assert (c != NULL);

	if (idsl_list_is_empty (c->l)) {
		return FALSE;
	}

	return (bool) (c->c == _idsl_node_get_pred (c->l->z));
}

bool
idsl_list_cursor_has_succ (const idsl_list_cursor_t c) {
	assert (c != NULL);

	return (bool) (_idsl_node_get_succ (c->c) != c->l->z);
}

bool
idsl_list_cursor_has_pred (const idsl_list_cursor_t c) {
	assert (c != NULL);

	return (bool) (_idsl_node_get_pred (c->c) != c->l->d);
}

void
idsl_list_cursor_set_content (idsl_list_cursor_t c, idsl_element_t e) {
	assert (c != NULL);

	if ((c->c == c->l->d) || (c->c == c->l->z)) {
		return;
	}

	_idsl_node_set_content (c->c, e);
}

idsl_element_t
idsl_list_cursor_get_content (const idsl_list_cursor_t c) {
	assert (c != NULL);

	if ((c->c == c->l->d) || (c->c == c->l->z)) {
		return NULL;
	}

	return _idsl_node_get_content (c->c);
}

idsl_element_t
idsl_list_cursor_insert_after (idsl_list_cursor_t c, void* v) {
	idsl_element_t e;
	_idsl_node_t n;

	assert (c != NULL);

	if ((c->c == c->l->d) || (c->c == c->l->z)) {
		return NULL;
	}

	n = _idsl_node_alloc ();
	if (n == NULL) {
		return NULL;
	}

	e = c->l->alloc_func (v);

	if (e == NULL) {
		_idsl_node_free (n);
		return NULL;
	}

	_idsl_node_set_content (n, e);
	_idsl_list_insert_after (n, c->c);

	c->l->card++;

	return e;
}

idsl_element_t
idsl_list_cursor_insert_before (idsl_list_cursor_t c, void* v) {
	idsl_element_t e;
	_idsl_node_t n;

	assert (c != NULL);

	if ((c->c == c->l->d) || (c->c == c->l->z)) {
		return NULL;
	}

	n = _idsl_node_alloc();
	if (n == NULL) {
		return NULL;
	}

	e = c->l->alloc_func(v);
	if (e == NULL) {
		_idsl_node_free (n);
		return NULL;
	}

	_idsl_node_set_content (n, e);
	_idsl_list_insert_before (n, c->c);

	return e;
}

idsl_element_t 
idsl_list_cursor_remove (idsl_list_cursor_t c) {
	idsl_element_t e;
	_idsl_node_t tmp;

	assert (c != NULL);

	if ((c->c == c->l->d) || (c->c == c->l->z)) {
		return NULL;
	}
	
	tmp = _idsl_node_get_succ (c->c);

	if (tmp == c->l->z) {
		return NULL;
	}

	_idsl_list_remove (tmp);
	e = _idsl_node_get_content (tmp);
	_idsl_node_free (tmp);

	c->l->card--;

	return e;
}

idsl_element_t
idsl_list_cursor_remove_after (idsl_list_cursor_t c) {
	idsl_element_t e;
	_idsl_node_t tmp;

	assert (c != NULL);

	if ((c->c == c->l->d) || (c->c == c->l->z)) {
		return NULL;
	}

	tmp = _idsl_node_get_succ (c->c);
	if (tmp == c->l->z) {
		return NULL;
	}

	_idsl_list_remove (tmp);
	e = _idsl_node_get_content (tmp);
	_idsl_node_free (tmp);

	c->l->card--;

	return e;
}

idsl_element_t
idsl_list_cursor_remove_before (idsl_list_cursor_t c) {
	idsl_element_t e;
	_idsl_node_t tmp;

	assert (c != NULL);

	if ((c->c == c->l->d) || (c->c == c->l->z)) {
		return NULL;
	}

	tmp = _idsl_node_get_pred (c->c);
	if (tmp == c->l->d) {
		return NULL;
	}
	
	_idsl_list_remove (tmp);
	e = _idsl_node_get_content (tmp);
	_idsl_node_free (tmp);

	c->l->card--;

	return e;
}

idsl_list_cursor_t
idsl_list_cursor_delete (idsl_list_cursor_t c) {
	idsl_element_t e;

	assert (c != NULL);

	e = idsl_list_cursor_remove (c);
	if (e != NULL) {
		c->l->free_func (e);
		return c;
	}

	return NULL;
}

idsl_list_cursor_t
idsl_list_cursor_delete_after (idsl_list_cursor_t c) {
	idsl_element_t e;

	assert (c != NULL);

	e = idsl_list_cursor_remove_after (c);
	if (e != NULL) {
		c->l->free_func (e);
		return c;
	}

	return NULL;
}

idsl_list_cursor_t
idsl_list_cursor_delete_before (idsl_list_cursor_t c) {
	idsl_element_t e;

	assert (c != NULL);

	e = idsl_list_cursor_remove_before (c);
	if (e != NULL) {
		c->l->free_func (e);
		return c;
	}

	return NULL;
}
		

	


/******************************************/
/* private func                           */
/******************************************/

static idsl_element_t
default_alloc (void* e) {
	return e;
}

static void
default_free (idsl_element_t e) {
	;
}

static _idsl_node_t 
search_by_function (idsl_list_t l, idsl_compare_func_t comp_f, const void* value) {
	_idsl_node_t left;
	_idsl_node_t right;

	left = _idsl_node_get_succ (l->d);
	right = _idsl_node_get_pred (l->z);

	while (left != _idsl_node_get_succ (right)) {
		if (comp_f (_idsl_node_get_content (left), (void*) value) == 0) {
			return left;
		}

		if (left == right) {
			return NULL;
		}

		if (comp_f (_idsl_node_get_content (right), (void*) value) == 0) {
			return right;
		}

		left = _idsl_node_get_succ (left);
		right = _idsl_node_get_pred (right);
	}

	return NULL;
}

static _idsl_node_t
search_by_position (idsl_list_t l, ulong pos) {
	ulong m;
	_idsl_node_t tmp;

	if (pos < 0 || pos > l->card) {
		return NULL;
	}

	m = (l->card / 2) + 1;

	if (pos < m) {
		tmp = _idsl_node_get_succ (l->d);

		while (pos > 1) {
			tmp =_idsl_node_get_succ (tmp);
			pos--;
		}
	} else {
		pos = l->card - pos;
		tmp = _idsl_node_get_pred (l->z);

		while (pos > 0) {
			tmp = _idsl_node_get_pred (tmp);
			pos--;
		}
	}

	return tmp;
}

static _idsl_node_t
sort (_idsl_node_t u, idsl_compare_func_t comp_f, _idsl_node_t z) {
	_idsl_node_t s;
	_idsl_node_t t;

	if (_idsl_node_get_succ (u) == z) {
		return u;
	}

	s = u;
	t = _idsl_node_get_succ (_idsl_node_get_succ (_idsl_node_get_succ(u)));
	while (t != z) {
		u = _idsl_node_get_succ (u);
		t = _idsl_node_get_succ (_idsl_node_get_succ(t));
	}

	t = _idsl_node_get_succ (u);
	_idsl_node_set_succ (u, z);

	return merge (sort (s, comp_f, z), sort(t, comp_f, z), comp_f, z);
}

static _idsl_node_t
merge (_idsl_node_t s, _idsl_node_t t, idsl_compare_func_t comp_f, _idsl_node_t z) {
	_idsl_node_t u = z;

	do {
		if (t == z) {
			_idsl_node_link (u, s);
			u = s;
			s = _idsl_node_get_succ (s);
			continue;
		}

		if (s == z) {
			_idsl_node_link (u, t);
			u = t;
			t =_idsl_node_get_succ (t);
			continue;
		}

		if (comp_f (_idsl_node_get_content (s), _idsl_node_get_content (t)) <= 0) {
			_idsl_node_link (u, s);
			u = s;
			s = _idsl_node_get_succ (s);
		} else {
			_idsl_node_link (u, t);
			u = t;
			t = _idsl_node_get_succ (t);
		}
	} while (u != z);

	u = _idsl_node_get_succ (z);
	_idsl_node_set_succ (z, z);

	return u;
}
		
static idsl_location_t
get_location (idsl_list_t list, _idsl_node_t node) {
	idsl_location_t location = IDSL_LOCATION_UNDEF;

	if (node == _idsl_node_get_succ (list->d)) {
		location |= IDSL_LOCATION_HEAD;
	}

	if (node == _idsl_node_get_pred (list->z)) {
		location |= IDSL_LOCATION_TAIL;
	}

	return location;
}

static idsl_element_t 
update_cursor (idsl_list_cursor_t c, _idsl_node_t n) {
	if (n == NULL) {
		return NULL;
	}

	c->c = n;

	return _idsl_node_get_content (n);
}
