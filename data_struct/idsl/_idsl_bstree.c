#include <stdlib.h>
#include <assert.h>

#include "idsl_types.h"
#include "_idsl_bstree.h"

#define LEFT(t) ( (_idsl_bstree_t) _idsl_bintree_get_left ((_idsl_bintree_t) (t)) )
#define RIGHT(t) ( (_idsl_bstree_t) _idsl_bintree_get_right ((_idsl_bintree_t) (t)) )
#define PARENT(t) ( (_idsl_bstree_t) _idsl_bintree_get_parent ((_idsl_bintree_t) (t)) )
#define CONTENT(t) ( _idsl_bintree_get_content ((_idsl_bintree_t) (t)) )

#define IS_LEAF(t) ( _idsl_bintree_is_leaf ((_idsl_bintree_t) (t)) )
#define IS_EMPTY(t) ( _idsl_bintree_is_empty ((_idsl_bintree_t) (t)) )

static idsl_element_t destroy_max (_idsl_bstree_t* t);

static idsl_element_t destroy_min (_idsl_bstree_t* t);

static void bstree_write (const _idsl_bstree_t t, const _idsl_bstree_write_func_t writf_f, FILE* file, void* user_data, bool dump);

_idsl_bstree_t _idsl_bstree_alloc (const idsl_element_t e) {
	return (_idsl_bstree_t) _idsl_bintree_alloc (e, NULL, NULL);
}

void _idsl_bstree_free (_idsl_bstree_t t, const idsl_free_func_t free_f) {
	_idsl_bintree_free ((_idsl_bintree_t) t, free_f);
}

_idsl_bstree_t _idsl_bstree_copy (const _idsl_bstree_t t, const idsl_copy_func_t copy_f) {
	assert (copy_f != NULL);

	return (_idsl_bstree_t) _idsl_bintree_copy ((_idsl_bintree_t) t, copy_f);
}

bool _idsl_bstree_is_empty (const _idsl_bstree_t t) {
	return IS_EMPTY(t);
}

bool _idsl_bstree_is_leaf (const _idsl_bstree_t t) {
	assert (!IS_EMPTY(t));

	return IS_LEAF(t);
}

bool _idsl_bstree_is_root (const _idsl_bstree_t t) {
	assert (!IS_EMPTY(t));

	return _idsl_bintree_is_root ((_idsl_bintree_t) (t));
}

idsl_element_t _idsl_bstree_get_content (const _idsl_bstree_t t) {
	assert (!IS_EMPTY(t));

	return CONTENT(t);
}

_idsl_bstree_t _idsl_bstree_get_parent (const _idsl_bstree_t t) {
	assert (!IS_EMPTY(t));

	return PARENT(t);
}

_idsl_bstree_t _idsl_bstree_get_left (const _idsl_bstree_t t) {
	assert (!IS_EMPTY(t));

	return LEFT(t);
}

_idsl_bstree_t _idsl_bstree_get_right (const _idsl_bstree_t t) {
	assert (!IS_EMPTY(t));

	return RIGHT(t);
}

ulong _idsl_bstree_get_size (const _idsl_bstree_t t) {
	return _idsl_bintree_get_size ((_idsl_bintree_t) t);
}

ulong _idsl_bstree_get_height (const _idsl_bstree_t t) {
	return _idsl_bintree_get_height ((_idsl_bintree_t) t);
}

_idsl_bstree_t _idsl_bstree_insert (_idsl_bstree_t* t, const idsl_compare_func_t comp_f, const idsl_element_t v, int* rc) {
	int comp = 0;
	_idsl_bintree_t parent = NULL;
	_idsl_bintree_t root = (_idsl_bintree_t) *t;
	_idsl_bstree_t n = NULL;

	assert (comp_f != NULL);
	assert (rc != NULL);

	*rc = IDSL_INSERTED;

	while (!IS_EMPTY (root)) {
		comp = comp_f(CONTENT(root), v);

		/* found */
		if (comp == 0) {
			*rc = IDSL_FOUND;
			return root;
		}

		parent = root;
		root = (comp > 0) ? LEFT(root) : RIGHT (root);
	}

	/* not found */
	n = (_idsl_bstree_t) _idsl_bintree_alloc (v, NULL, NULL);
	if (n == NULL) {
		*rc = IDSL_ERR_MEM_ALLOC;
		return NULL;
	}

	_idsl_bintree_set_parent (n, parent);

	/* that means *t is NULL */
	if (parent == NULL) {
		*t = n;
		return n;
	}

	if (comp > 0) {
		_idsl_bintree_set_left (parent, n);
	} else {
		_idsl_bintree_set_right (parent, n);
	}

	return n;
}

idsl_element_t _idsl_bstree_remove (_idsl_bstree_t* t, const idsl_compare_func_t comp_f, const idsl_element_t v) {
	idsl_element_t e;
	_idsl_bstree_t l;
	_idsl_bstree_t r;

	assert (comp_f != NULL);

	if (IS_EMPTY(*t)) {
		return NULL;
	}

	e = CONTENT(*t);

	{
		int comp = comp_f (v, e);

		if (comp < 0) {
			return _idsl_bstree_remove (_idsl_bintree_get_left_ref (*t), comp_f, v);
		} else if (comp > 0) {
			return _idsl_bstree_remove (_idsl_bintree_get_right_ref (*t), comp_f, v);
		}
	}

	/* comp == 0 */
	l = LEFT (*t);
	r = RIGHT (*t);

	if (IS_EMPTY(l)) {
		e = CONTENT (*t);
		free (*t);

		if (!IS_EMPTY(r)) {
			_idsl_bintree_set_parent(r, r);
		}
		
		*t = r;
		return e;
	}

	if (IS_EMPTY(r)) {
		e = CONTENT (*t);
		free (*t);

		if (!IS_EMPTY(l)) {
			_idsl_bintree_set_parent (l, l);
		}

		*t = l;
		return e;
	}


	/* if *t has two child, destroy the max vaule in left tree, and set the value to *t */
	_idsl_bintree_set_content ((_idsl_bintree_t) (*t), destroy_max (_idsl_bintree_get_left_ref (*t)));

	return e;
}

_idsl_bstree_t _idsl_bstree_search (const _idsl_bstree_t t, const idsl_compare_func_t comp_f, const idsl_element_t v) {
	_idsl_bstree_t tmp = t;

	assert (comp_f != NULL);

	while (!IS_EMPTY(tmp)) {
		int comp = comp_f (CONTENT(tmp), v);

		if (comp == 0) {
			return tmp;
		} else if (comp > 0) {
			tmp = LEFT(tmp);
		} else {
			tmp = RIGHT(tmp);
		}
	}

	return NULL;
}

_idsl_bstree_t _idsl_bstree_search_next (const _idsl_bstree_t t, const idsl_compare_func_t comp_f, const idsl_element_t v) {
	_idsl_bstree_t b;
	_idsl_bstree_t c;

	assert (comp_f != NULL);

	b = _idsl_bstree_search(t, comp_f, v);

	if (IS_EMPTY(b)) {
		return NULL;
	}

	c = (_idsl_bstree_t) _idsl_bintree_get_right ((_idsl_bintree_t) b);

	if (!IS_EMPTY(c)) {
		while (!IS_EMPTY (_idsl_bintree_get_left ((_idsl_bintree_t) c)))
			c = (_idsl_bstree_t) _idsl_bintree_get_left ((_idsl_bintree_t) c);
		return c;
	}

	c = (_idsl_bstree_t) _idsl_bintree_get_parent ((_idsl_bintree_t) b);

	while (b != t && (_idsl_bstree_t) _idsl_bintree_get_right ((_idsl_bintree_t) c) == b) {
		b = c;
		c = (_idsl_bstree_t) _idsl_bintree_get_parent ((_idsl_bintree_t) c);
	}

	if ((_idsl_bstree_t) _idsl_bstree_get_left ((_idsl_bintree_t) c) == b) {
		return c;
	}

	return NULL;
}

_idsl_bstree_t _idsl_bstree_map_prefix (const _idsl_bstree_t t, const _idsl_bstree_map_func_t map_f, void* user_data) {
	assert (map_f != NULL);

	if (!IS_EMPTY (t)) {
		if (map_f (t, user_data) == IDSL_MAP_STOP) {
			return t;
		}

		_idsl_bstree_map_prefix ((_idsl_bstree_t) _idsl_bintree_get_left ((_idsl_bintree_t) t), map_f, user_data);
		_idsl_bstree_map_prefix ((_idsl_bstree_t) _idsl_bintree_get_right ((_idsl_bintree_t) t), map_f, user_data);
	}

	return NULL;
}

_idsl_bstree_t _idsl_bstree_map_infix (const _idsl_bstree_t t, const _idsl_bstree_map_func_t map_f, void* user_data) {
	assert (map_f != NULL);

	if (!IS_EMPTY(t)) {
		_idsl_bstree_map_infix ((_idsl_bstree_t) _idsl_bintree_get_left ((_idsl_bintree_t) t), map_f, user_data);

		if (map_f (t, user_data) == IDSL_MAP_STOP) {
			return t;
		}

		_idsl_bstree_map_infix ((_idsl_bstree_t) _idsl_bintree_get_right ((_idsl_bintree_t) t), map_f, user_data);
	}

	return NULL;
}

_idsl_bstree_t _idsl_bstree_map_postfix (const _idsl_bstree_t t, const _idsl_bstree_map_func_t map_f, void* user_data) {
	assert (map_f != NULL);

	if (!IS_EMPTY(t)) {
		_idsl_bstree_map_postfix ((_idsl_bstree_t) _idsl_bintree_get_left ((_idsl_bintree_t) t), map_f, user_data);
		_idsl_bstree_map_postfix ((_idsl_bstree_t) _idsl_bintree_get_right ((_idsl_bintree_t) t), map_f, user_data);

		if (map_f (t, user_data) == IDSL_MAP_STOP) {
			return t;
		}

	}

	return NULL;
}

void _idsl_bstree_write (const _idsl_bstree_t t, const _idsl_bstree_write_func_t write_f, FILE* file, void* user_data) {
	assert (write_f != NULL);
	assert (file != NULL);

	_idsl_bintree_write ((_idsl_bintree_t) t, write_f, file, user_data);
}

void _idsl_bstree_write_xml (const _idsl_bstree_t t, const _idsl_bstree_write_func_t write_f, FILE* file, void* user_data) {
	assert (file != NULL);

	fprintf (file, "<_IDSL_BSTREE>\n");
	bstree_write (t, write_f, file, user_data, FALSE);
	fprintf (file, "</_IDSL_BSTREE>\n");
}

void _idsl_bstree_dump (const _idsl_bstree_t t, const _idsl_bstree_write_func_t write_f, FILE* file, void *user_data) {
	assert (file != NULL);

	fprintf (file, "<_IDSL_BSTREE REF=\"%p\">\n", (void*) t);
	bstree_write (t, write_f, file, user_data, TRUE);
	fprintf (file, "</_IDSL_BSTREE>\n");
}
	

/****************
 * private func
 * *************/

static idsl_element_t destroy_max (_idsl_bstree_t* tree) {
	if (IS_EMPTY (RIGHT (*tree))) {
		idsl_element_t max = CONTENT (*tree);
		_idsl_bstree_t t = LEFT (*tree);
		free (*tree);
		*tree = t;
		return max;
	}

	return destroy_max (_idsl_bintree_get_right_ref (*tree));
}

static idsl_element_t destroy_min (_idsl_bstree_t* tree) {
	if (IS_EMPTY (LEFT (*tree))) {
		idsl_element_t min = CONTENT (*tree);
		_idsl_bstree_t t = RIGHT(*tree);
		free(*tree);
		*tree = t;
		return min;
	}

	return destroy_min (_idsl_bintree_get_left_ref (*tree));
}

void bstree_write (const _idsl_bstree_t t, const _idsl_bstree_write_func_t write_f, FILE* file, void* user_data, bool dump) {
	if (!IS_EMPTY(t)) {
		bstree_write (LEFT (t), write_f, file, user_data, dump);

		if (IS_LEAF (t)) {
			fprintf (file, "<_IDSL_BSTREE_LEAF REF=\"%p\"", (void*) t);
		} else {
			fprintf (file, "<_IDSL_BSTREE_NODE REF=\"%p\"", (void*) t);
		}

		if (dump == TRUE) {
			if (CONTENT (t) != NULL) {
				fprintf (file, " CONTENT=\"%p\"", (void*) CONTENT(t));
			} else {
				fprintf (file, " CONTENT=\"\"");
			}
		}

		if (!IS_LEAF(t)) {
			if ( LEFT(t) != NULL) {
				fprintf (file, " LEFT=\"%p\"", (void*) LEFT(t));
			} else {
				fprintf (file, " LEFT=\"\"");
			}

			if ( RIGHT(t) != NULL) {
				fprintf (file, " RIGHT=\"%p\"", (void*) RIGHT(t));
			} else {
				fprintf (file, " RIGHT=\"\"");
			}
		}

		fprintf (file, " PARENT=\"%p\"", (void*) PARENT(t));

		if (write_f != NULL) {
			write_f (t, file, user_data);
		}

		if (IS_LEAF (t)) {
			fprintf (file, "</_IDSL_BSTREE_LEAF>\n");
		} else {
			fprintf (file, "</_IDSL_BSTREE_NODE>\n");
		}

		bstree_write (RIGHT(t), write_f, file, user_data, dump);
	}
}


