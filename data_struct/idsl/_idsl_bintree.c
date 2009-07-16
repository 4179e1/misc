#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "_idsl_bintree.h"
#include "idsl_types.h"
#include "idsl_macros.h"

#define LEFT(t) ((t)->left)
#define RIGHT(t) ((t)->right)
#define PARENT(t) ((t)->parent)
#define CONTENT(t) ((t)->content)

#define IS_LEAF(t) ((LEFT(t) == NULL) && (RIGHT(t) == NULL))
#define IS_EMPTY(t) ((t) == NULL)

struct _idsl_bintree {
	struct _idsl_bintree* left;
	struct _idsl_bintree* right;
	struct _idsl_bintree* parent;
	idsl_element_t content;
};

static void bintree_free (_idsl_bintree_t t);
static void bintree_free_with_func (_idsl_bintree_t t, idsl_free_func_t f);
static void bintree_write (const _idsl_bintree_t t, const _idsl_bintree_write_func_t write_f, FILE* file, void *data, bool dump);


_idsl_bintree_t _idsl_bintree_alloc (const idsl_element_t e, const _idsl_bintree_t l, const _idsl_bintree_t r) {
	_idsl_bintree_t t;
	t = (_idsl_bintree_t) malloc (sizeof(struct _idsl_bintree));
	if (t == NULL) {
		return NULL;
	}

	t->left = l;
	t->right = r;
	if (l != NULL) {
		l->parent = t;
	}
	if (r != NULL) {
		l->parent = t;
	}

	t->parent = t;
	t->content = e;

	return t;
}

void _idsl_bintree_free (_idsl_bintree_t t, const idsl_free_func_t free_f) {
	(free_f == NULL) ? bintree_free (t) : bintree_free_with_func (t, free_f);
}

_idsl_bintree_t _idsl_bintree_copy (const _idsl_bintree_t t, const idsl_copy_func_t copy_f) {
	_idsl_bintree_t tmp;

	assert (copy_f != NULL);

	if (IS_EMPTY(t)) {
		return NULL;
	}

	tmp = _idsl_bintree_alloc (copy_f (CONTENT(t)), NULL, NULL);
	if (tmp == NULL) {
		return NULL;
	}

	tmp->left = _idsl_bintree_copy (LEFT(t), copy_f);
	if (tmp->left != NULL) {
		tmp->left->parent = tmp;
	}

	tmp->right = _idsl_bintree_copy (RIGHT(t), copy_f);
	if (tmp->right != NULL) {
		tmp->right->parent = tmp;
	}

	return tmp;
}

bool _idsl_bintree_is_empty (const _idsl_bintree_t t) {
	return (bool) IS_EMPTY(t);
}

bool _idsl_bintree_is_leaf (const _idsl_bintree_t t) {
	return (bool) IS_LEAF(t);
}

bool _idsl_bintree_is_root (const _idsl_bintree_t t) {
	assert (!IS_EMPTY(t));

	return (bool) (PARENT(t) == t);
}

idsl_element_t _idsl_bintree_get_content (const _idsl_bintree_t t) {
	assert (!IS_EMPTY(t));

	return CONTENT(t);
}

_idsl_bintree_t _idsl_bintree_get_parent (const _idsl_bintree_t t) {
	assert (!IS_EMPTY(t));

	return PARENT(t);
}

_idsl_bintree_t _idsl_bintree_get_left (const _idsl_bintree_t t) {
	assert (!IS_EMPTY(t));

	return LEFT(t);
}

_idsl_bintree_t _idsl_bintree_get_right (const _idsl_bintree_t t) {
	assert (!IS_EMPTY(t));

	return RIGHT(t);
}

_idsl_bintree_t* _idsl_bintree_get_left_ref (const _idsl_bintree_t t) {
	assert (!IS_EMPTY(t));

	return &LEFT(t);
}

_idsl_bintree_t* _idsl_bintree_get_right_ref (const _idsl_bintree_t t) {
	assert (!IS_EMPTY(t));

	return &RIGHT(t);
}

ulong _idsl_bintree_get_height (const _idsl_bintree_t t) {
	if (IS_EMPTY(t)) {
		return 0UL;
	}

	if (IS_LEAF(t)) {
		return 0UL;
	}

	return (ulong) (1UL + IDSL_MAX (_idsl_bintree_get_height (LEFT(t)), _idsl_bintree_get_height(RIGHT(t))));
}

ulong _idsl_bintree_get_size (const _idsl_bintree_t t) {
	if (IS_EMPTY (t)) {
		return 0UL;
	}

	return (ulong) (1UL + _idsl_bintree_get_size (LEFT(t)) + _idsl_bintree_get_size (RIGHT(t)));
}

/* e should not be lost */
void _idsl_bintree_set_content (_idsl_bintree_t t, const idsl_element_t e) {
	assert (!IS_EMPTY (t));

	t->content = e;
}

void _idsl_bintree_set_parent (_idsl_bintree_t t, const _idsl_bintree_t p) {
	assert (!IS_EMPTY(t));

	if (p != NULL) {
		t->parent = p;
	}
}

void _idsl_bintree_set_left (_idsl_bintree_t t, const _idsl_bintree_t l ) {
	assert (!IS_EMPTY(t));

	t->left = l;

	if (l != NULL) {
		l->parent = t;
	}
}

void _idsl_bintree_set_right (_idsl_bintree_t t, const _idsl_bintree_t r) {
	assert (!IS_EMPTY(t));

	t->right = r;

	if (r != NULL) {
		r->parent = t;
	}
}

_idsl_bintree_t _idsl_bintree_rotate_left (_idsl_bintree_t* t) {
	_idsl_bintree_t rn;

	assert(!IS_EMPTY (*t));
	assert(!IS_EMPTY (RIGHT(*t)));

	rn = RIGHT (*t);
	(*t)->right = LEFT(rn);

	if (LEFT(rn) != NULL) {
		rn->left->parent = *t;
	}

	rn->parent = PARENT (*t);

	rn->left = (*t);
	(*t)->parent = rn;
	*t = rn;

	return rn;
}

_idsl_bintree_t _idsl_bintree_rotate_right (_idsl_bintree_t* t) {
	_idsl_bintree_t ln;

	assert (!IS_EMPTY(*t));
	assert (!IS_EMPTY(LEFT(*t)));

	ln = LEFT(*t);
	(*t)->left = RIGHT(ln);

	if (RIGHT(ln) != NULL) {
		ln->right->parent = *t;
	}

	ln->parent = PARENT(*t);

	ln->right = (*t);
	(*t)->parent = ln;
	*t = ln;

	return ln;
}

_idsl_bintree_t _idsl_bintree_rotate_left_right (_idsl_bintree_t *t) {
	assert (!IS_EMPTY(*t));
	assert (!IS_EMPTY(LEFT(*t)));
	assert (!IS_EMPTY(RIGHT(LEFT(*t))));

	_idsl_bintree_rotate_left (&LEFT(*t));

	return _idsl_bintree_rotate_right (t);
}

_idsl_bintree_t _idsl_bintree_rotate_right_left (_idsl_bintree_t *t) {
	assert (!IS_EMPTY(*t));
	assert (!IS_EMPTY(RIGHT(*t)));
	assert (!IS_EMPTY(LEFT(RIGHT(*t))));

	_idsl_bintree_rotate_right (&RIGHT(*t));

	return _idsl_bintree_rotate_left (t);
}

_idsl_bintree_t _idsl_bintree_map_prefix (const _idsl_bintree_t t, const _idsl_bintree_map_func_t map_f, void *d) {
	assert (map_f != NULL);

	if (!IS_EMPTY(t)) {
		if (map_f (t, d) == IDSL_MAP_STOP) {
			return t;
		}

		_idsl_bintree_map_prefix (LEFT(t), map_f, d);
		_idsl_bintree_map_prefix (RIGHT(t), map_f, d);
	}

	return NULL;
}

_idsl_bintree_t _idsl_bintree_map_infix (const _idsl_bintree_t t, const _idsl_bintree_map_func_t map_f, void *d) {
	assert (map_f != NULL);

	if (!IS_EMPTY(t)) {
		_idsl_bintree_map_infix (LEFT(t), map_f, d);

		if (map_f (t, d) == IDSL_MAP_STOP) {
			return t;
		}

		_idsl_bintree_map_infix (RIGHT(t), map_f, d);
	}

	return NULL;
}

_idsl_bintree_t _idsl_bintree_map_postfix (const _idsl_bintree_t t, const _idsl_bintree_map_func_t map_f, void *d) {
	assert (map_f != NULL);

	if (!IS_EMPTY(t)) {
		_idsl_bintree_map_postfix (LEFT(t), map_f, d);
		_idsl_bintree_map_postfix (RIGHT(t), map_f, d);

		if (map_f (t, d) == IDSL_MAP_STOP) {
			return t;
		}
	}

	return NULL;
}


void _idsl_bintree_write (const _idsl_bintree_t t, const _idsl_bintree_write_func_t write_f, FILE* file, void* user_data) {
	assert (write_f != NULL);
	assert (file != NULL);

	if (!IS_EMPTY(t)) {
		write_f (t, file, user_data);
		_idsl_bintree_write (LEFT(t), write_f, file, user_data);
		_idsl_bintree_write (RIGHT(t), write_f, file, user_data);
	}
}

void _idsl_bintree_write_xml (const _idsl_bintree_t t, const _idsl_bintree_write_func_t write_f, FILE *file, void *user_data) {
	assert (file != NULL);

	fprintf (file, "<_IDSL_BINTREE ROOT=\"%p\">\n", (void*) t);
	bintree_write (t, write_f, file, user_data, FALSE);
	fprintf (file, "</_IDLS_BINTREE>\n");
}

void _idsl_bintree_dump (const _idsl_bintree_t t, const _idsl_bintree_write_func_t write_f, FILE *file, void *user_data) {
	assert (file != NULL);

	fprintf (file, "<_IDSL_BINTREE ROOT=\"%p\">\n", (void*) t);
	bintree_write (t, write_f, file, user_data, TRUE);
	fprintf (file, "</_IDLS_BINTREE>\n");
}

/***************
 * private func
 * ************/

static void bintree_free (_idsl_bintree_t t) {
	if (!IS_EMPTY(t)) {
		bintree_free (LEFT(t));
		bintree_free (RIGHT(t));
		free(t);
	}
}

static void bintree_free_with_func (_idsl_bintree_t t, idsl_free_func_t free_f ) {
	if (!IS_EMPTY (t)) {
		bintree_free_with_func (LEFT (t), free_f);
		bintree_free_with_func (RIGHT(t), free_f);

		free_f (CONTENT(t));
		free (t);
	}
} 

static void bintree_write (const _idsl_bintree_t t, const _idsl_bintree_write_func_t write_f, FILE *file, void *d, bool dump) {
	if (!IS_EMPTY(t)) {
		if (IS_LEAF(t)) {
			fprintf (file, "<_IDSL_BINTREE_LEAF REF=\"%p\"", (void*)t);
		} else {
			fprintf (file, "<_IDSL_BINTREE_NODE REF=\"%p\"", (void*)t);
		}

		if (dump == TRUE) {
			if (CONTENT(t)) {
				fprintf (file, " CONTENT=\"%p\"", (void*)CONTENT(t));
			} else {
				fprintf (file, " CONTENT=\"\"");
			}
		}

		if (!IS_LEAF (t)) {
			if (LEFT(t) != NULL) {
				fprintf (file, " LEFT=\"%p\"", (void*)LEFT(t));
			} else {
				fprintf (file, " LEFT=\"\"");
			}

			if (RIGHT(t) != NULL) {
				fprintf (file, " RIGHT=\"%p\"", (void*)RIGHT(t));
			} else {
				fprintf (file, " RIGHT=\"\"");
			}
		}

		if (PARENT(t) != t) {
			fprintf (file, " PARENT=\"%p\"", (void*)PARENT(t));
		} else {
			fprintf (file, " PARENT=\"\"");
		}

		fprintf (file, ">");

		if (write_f != NULL) {
			write_f (t, file, d);
		}

		if (IS_LEAF(t)) {
			fprintf (file, "</_IDSL_BINTREE_LEAF>\n");
		} else {
			fprintf (file, "</_IDLS_BINTREE_NODE>\n");
		}

		bintree_write (LEFT(t), write_f, file, d, dump);
		bintree_write (RIGHT(t), write_f, file, d, dump);
	}
}
