#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "_idsl_node.h"
#include "idsl_types.h"
#include "_idsl_list.h"

_idsl_list_t
_idsl_list_alloc (const idsl_element_t e) {
	_idsl_list_t list;

	list = _idsl_node_alloc ();

	if (list == NULL) {
		return NULL;
	}

	_idsl_node_set_content (list, e);

	return list;
}

void
_idsl_list_free (_idsl_list_t list, const idsl_free_func_t free_f) {
	_idsl_node_t save;

	if (free_f != NULL) {
		while (list != NULL) {
			save = _idsl_node_get_succ (list);
			free_f (_idsl_node_get_content(list));
			_idsl_node_free (list);
			list = save;
		}
		return;
	}

	while (list != NULL) {
		save = _idsl_node_get_succ (list);
		_idsl_node_free (list);
		list = save;
	}
}

bool
_idsl_list_is_empty (const _idsl_list_t list) {
	return (bool) (list == NULL);
}

ulong
_idsl_list_get_size (const _idsl_list_t list) {
	ulong card;
	_idsl_list_t save;

	card = 0;

	for (save = list; save != NULL; save = _idsl_node_get_succ(save)) {
		card++;
	}

	return card;
}

void
_idsl_list_link (_idsl_list_t list_1, _idsl_list_t list_2) {
	_idsl_node_t tmp;

	assert (list_1 != NULL);
	assert (list_2 != NULL);

	tmp = list_1;

	while (_idsl_node_get_succ (tmp) != NULL) {
		tmp = _idsl_node_get_succ(tmp);
	}

	_idsl_node_link (tmp, list_2);
}

void
_idsl_list_insert_after (_idsl_list_t list, _idsl_list_t prev) {
	_idsl_node_t prev_succ;

	assert (list != NULL);
	assert (prev != NULL);
	
	/**************************************************/
	/* list_prev: ------prev            -----------   */
	/* list:                list--------              */                 
	/**************************************************/

	prev_succ = _idsl_node_get_succ (prev);
	_idsl_node_link (prev, list);

	if (prev_succ != NULL) {
		_idsl_list_link (list, prev_succ);
	}
}

void
_idsl_list_insert_before (_idsl_list_t list, _idsl_list_t succ) {
	_idsl_node_t succ_prev;

	assert (list != NULL);
	assert (succ != NULL);

	/**************************************************/
	/* list_succ: ------            succ-----------   */
	/* list:            list--------                  */                 
	/**************************************************/

	succ_prev = _idsl_node_get_pred (succ);
	if (succ_prev != NULL) {
		_idsl_node_link (succ_prev, list);
	}

	_idsl_list_link (list, succ);
}

void
_idsl_list_remove (_idsl_node_t node) {
	_idsl_node_t succ;
	_idsl_node_t pred;

	assert (node != NULL);

	succ = _idsl_node_get_succ (node);
	pred = _idsl_node_get_pred (node);

	if (succ != NULL) {
		_idsl_node_set_pred (succ, pred);
	}

	if (pred != NULL) {
		_idsl_node_set_succ (pred, succ);
	}
/* memory leak ? */
/* the caller func have a copy of node, it should be free by caller func */
	_idsl_node_set_pred (node, NULL);
	_idsl_node_set_succ (node, NULL);
}

_idsl_list_t
_idsl_list_search (const _idsl_list_t list, const idsl_compare_func_t comp_f, void* user_data) {
	_idsl_node_t tmp;

	assert (comp_f != NULL);

	for (tmp = list; tmp != NULL; tmp = _idsl_node_get_succ(tmp)) {
		if (comp_f (_idsl_node_get_content(tmp), user_data) == 0) {
			return tmp;
		}
	}

	return NULL;
}

_idsl_list_t
_idsl_list_map_forward (const _idsl_list_t list, const _idsl_node_map_func_t map_f, void* user_data) {
	_idsl_node_t tmp;

	assert (map_f != NULL);

	for (tmp = list; tmp != NULL; tmp = _idsl_node_get_succ(tmp)) {
		if (map_f (tmp, user_data) == IDSL_MAP_STOP) {
			return tmp;
		}
	}

	return NULL;
}

_idsl_list_t
_idsl_list_map_backward (const _idsl_list_t list, const _idsl_node_map_func_t map_f, void* user_data) {
	_idsl_node_t tmp;

	tmp = list;
	while (_idsl_node_get_succ(tmp) != NULL) {
		tmp = _idsl_node_get_succ(tmp);
	}

	while (tmp != NULL) {
		if (map_f (tmp, user_data) == IDSL_MAP_STOP) {
			return tmp;
		}

		tmp = _idsl_node_get_pred (tmp);
	}

	return NULL;
}

void
_idsl_list_write (const _idsl_list_t list, const _idsl_node_write_func_t write_f, FILE* file, void* user_data) {
	_idsl_node_t tmp;
	
	assert (write_f != NULL);
	assert (file != NULL);

	for (tmp = list; tmp != NULL; tmp = _idsl_node_get_succ(tmp)) {
		_idsl_node_write (tmp, write_f, file, user_data);
	}
}

void
_idsl_list_write_xml (const _idsl_list_t list, const _idsl_node_write_func_t write_f, FILE* file, void* user_data) {
	_idsl_node_t tmp;

	assert (file != NULL);

	fprintf (file, "<_IDSL_LIST>\n");

	for (tmp = list; tmp != NULL; tmp = _idsl_node_get_succ(tmp)) {
		_idsl_node_write_xml (tmp, write_f, file, user_data);
	}

	fprintf (file, "</IDSL_LIST>\n");
}

void
_idsl_list_dump (const _idsl_list_t list, const _idsl_node_write_func_t write_f, FILE* file, void* user_data) {
	_idsl_node_t tmp;

	assert (file != NULL);

	fprintf (file, "<_IDSL_LIST REF=\"%p\"", (void*) list);

	for (tmp = list; tmp != NULL; tmp = _idsl_node_get_succ(tmp)) {
		_idsl_node_dump (tmp, write_f, file, user_data);
	}

	fprintf (file, "</IDSL_LIST>\n");
}
