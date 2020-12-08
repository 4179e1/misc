#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "idsl_types.h"
#include "_idsl_bintree.h"
#include "idsl_bstree.h"
#include "idsl_macros.h"

#define LEFT(t)		( _idsl_bintree_get_left ((t)) )
#define RIGHT(t)	( _idsl_bintree_get_right ((t)) )
#define CONTENT(t)	( _idsl_bintree_get_content ((t)) )
#define PARENT(t)	( _idsl_bintree_get_parent ((t)) )
#define SENT(t)		( (t)->sent )
#define ROOT(t)		( _idsl_bintree_get_right (SENT(t)))

struct idsl_bstree {
	char* name;
	ulong card;
	_idsl_bintree_t sent;

	idsl_alloc_func_t alloc_f;
	idsl_free_func_t free_f;
	idsl_compare_func_t comp_f;
};


static idsl_element_t 
default_alloc (void* e);

static void 
default_free (idsl_element_t e);

static long int 
default_comp (idsl_element_t, void* key);

static void 
bstree_free (_idsl_bintree_t n, _idsl_bintree_t sent, idsl_free_func_t f);

static ulong 
bstree_height (_idsl_bintree_t n, _idsl_bintree_t sent);

static _idsl_bintree_t 
bstree_search (_idsl_bintree_t n, _idsl_bintree_t sent, idsl_compare_func_t f, void* v);

static _idsl_bintree_t 
bstree_next (idsl_bstree_t t, _idsl_bintree_t n);

static idsl_element_t 
bstree_prefix_parse (_idsl_bintree_t t, _idsl_bintree_t sent, idsl_map_func_t f, void* d);

static idsl_element_t
bstree_infix_parse (_idsl_bintree_t t, _idsl_bintree_t sent, idsl_map_func_t f, void* d);

static idsl_element_t
bstree_postfix_parse (_idsl_bintree_t t, _idsl_bintree_t sent, idsl_map_func_t f, void* d);

static void
bstree_write (_idsl_bintree_t n, _idsl_bintree_t sent, idsl_write_func_t f, FILE* file, void* d);

static void
bstree_write_xml (_idsl_bintree_t n, _idsl_bintree_t sent, idsl_write_func_t f, FILE* file, void* d);

static void
bstree_dump (_idsl_bintree_t n, _idsl_bintree_t sent, idsl_write_func_t f, FILE* file, void* d);

static idsl_location_t
get_location (_idsl_bintree_t t, _idsl_bintree_t n);


idsl_bstree_t idsl_bstree_alloc (const char* name, const idsl_alloc_func_t alloc_f, idsl_free_func_t free_f, idsl_compare_func_t comp_f) {
	idsl_bstree_t t;

	t = (idsl_bstree_t) malloc (sizeof (struct idsl_bstree));
	if (t == NULL) {
		return NULL;
	}

	t->sent = _idsl_bintree_alloc (NULL, NULL, NULL);
	if (t->sent == NULL) {
		free(t);
		return NULL;
	}

	_idsl_bintree_set_parent ((_idsl_bintree_t) (t->sent), (_idsl_bintree_t) (t->sent));
	_idsl_bintree_set_left ((_idsl_bintree_t) (t->sent), (_idsl_bintree_t) (t->sent));
	_idsl_bintree_set_right ((_idsl_bintree_t) (t->sent), (_idsl_bintree_t) (t->sent));

	t->name = NULL;

	if (idsl_bstree_set_name (t, name) == NULL) {
		free (t);
		return NULL;
	}

	t->comp_f = comp_f ? comp_f : default_comp;
	t->alloc_f = alloc_f ? alloc_f : default_alloc;
	t->free_f = free_f ? free_f : default_free;

	t->card = 0UL;

	return t;
}

void
idsl_bstree_free (idsl_bstree_t t) {
	assert (t != NULL);

	bstree_free (ROOT(t), SENT(t), t->free_f);

	_idsl_bintree_set_left ((_idsl_bintree_t) SENT(t), NULL);
	_idsl_bintree_set_right ((_idsl_bintree_t) SENT(t), NULL);
	_idsl_bintree_free (SENT(t), NULL);

	if (t->name != NULL) {
		free (t->name);
	}

	free (t);
}

void idsl_bstree_flush (idsl_bstree_t t) {
	assert (t != NULL);

	bstree_free (ROOT(t), SENT(t), t->free_f);
	_idsl_bintree_set_left ((_idsl_bintree_t) SENT(t), (_idsl_bintree_t) SENT(t));
	_idsl_bintree_set_right ((_idsl_bintree_t) SENT(t), (_idsl_bintree_t) SENT(t));
	t->card = 0UL;
}

const char* 
idsl_bstree_get_name (const idsl_bstree_t t) {
	assert (t != NULL);

	return t->name;
}

bool 
idsl_bstree_is_empty (const idsl_bstree_t t) {
	assert (t != NULL);

	return (bool) (t->card == 0);
}

idsl_element_t
idsl_bstree_get_root (const idsl_bstree_t t) {
	assert (t != NULL);

	return CONTENT (ROOT(t));
}

ulong idsl_bstree_get_size (const idsl_bstree_t t) {
	assert (t != NULL);

	return t->card;
}

ulong idsl_bstree_get_height (const idsl_bstree_t t) {
	assert (t != NULL);

	return bstree_height (ROOT (t), SENT(t));
}

idsl_bstree_t idsl_bstree_set_name (idsl_bstree_t t, const char* name) {
	assert (t != NULL);

	if (t->name != NULL) {
		free (t->name);
		t->name = NULL;
	}

	if (name != NULL) {
		t->name = (char*) malloc ((strlen (name) + 1) * sizeof (char));

		if (t->name == NULL) {
			return NULL;
		}
		strcpy (t->name, name);
	}

	return t;
}

idsl_element_t idsl_bstree_insert (idsl_bstree_t t, void* v, int* rc) {
	int comp = 0;
	idsl_element_t e;
	_idsl_bintree_t root;
	_idsl_bintree_t parent;
	_idsl_bintree_t n;

	assert (t != NULL);
	assert (rc != NULL);

	*rc = IDSL_INSERTED;

	root = ROOT (t);
	parent = SENT (t);
	while (root != SENT (t)) {
		parent = root;
		comp = t->comp_f (CONTENT (root), v);

		if (comp == 0) {
			*rc = IDSL_FOUND;
			return CONTENT(root);
		}

		root = (comp > 0) ? LEFT (root) : RIGHT (root);
	}

	e = (t->alloc_f) (v);
	if (e == NULL) {
		*rc = IDSL_ERR_MEM_ALLOC;
		return NULL;
	}

	n = _idsl_bintree_alloc (e, NULL, NULL);
	if (n == NULL) {
		t->free_f (e);
		*rc = IDSL_ERR_MEM_ALLOC;
		return NULL;
	}

	_idsl_bintree_set_parent ((_idsl_bintree_t) n, (_idsl_bintree_t) parent);
	_idsl_bintree_set_left ((_idsl_bintree_t) n, (_idsl_bintree_t) SENT(t));
	_idsl_bintree_set_right ((_idsl_bintree_t) n, (_idsl_bintree_t) SENT(t));

	if (parent == SENT(t) || comp < 0) {
		_idsl_bintree_set_right ((_idsl_bintree_t) parent, (_idsl_bintree_t) n);
	} else { /* if comp > 0*/
		_idsl_bintree_set_left ((_idsl_bintree_t) parent, (_idsl_bintree_t) n);
	}

	t->card++;

	return e;
}

idsl_element_t idsl_bstree_remove (idsl_bstree_t t, void* v) {
	idsl_element_t e;
	_idsl_bintree_t n;
	_idsl_bintree_t child;

	assert (t != NULL);

	n = bstree_search (ROOT(t), SENT(t), t->comp_f, v);
	if ( n == NULL) {
		return NULL;
	}

	if (LEFT(n) != SENT (t) && RIGHT(n) != SENT(t)) { /* not leaf */
		_idsl_bintree_t next = bstree_next (t, n);
		_idsl_bintree_t nextparent = PARENT (next);

		child = RIGHT(next);
		_idsl_bintree_set_parent (child, nextparent);

		if (LEFT (nextparent) == next) {
			_idsl_bintree_set_left (nextparent, child);
		} else {
			_idsl_bintree_set_right (nextparent, child);
		}

		_idsl_bintree_set_parent (next, PARENT(n));
		_idsl_bintree_set_left (next, LEFT(n));
		_idsl_bintree_set_parent (next, RIGHT(n));
		_idsl_bintree_set_parent (LEFT(next), next);
		_idsl_bintree_set_parent (RIGHT(next), next);

		if (LEFT( PARENT (n)) == n) {
			_idsl_bintree_set_left (PARENT (n), next);
		} else {
			_idsl_bintree_set_right (PARENT (n), next);
		}
	} else { /* leaf */
		child = LEFT (n) != SENT (t) ? LEFT(n) : RIGHT(n);

		if (n == LEFT (PARENT(n))) {
			_idsl_bintree_set_left (PARENT(n), child);
		} else {
			_idsl_bintree_set_right (PARENT(n), child);
		}
	}

	t->card--;

	e = CONTENT(n);
	_idsl_bintree_set_left ((_idsl_bintree_t) n, NULL);
	_idsl_bintree_set_right ((_idsl_bintree_t) n, NULL);
	_idsl_bintree_free (n, NULL);

	return e;
}

idsl_bstree_t idsl_bstree_delete (idsl_bstree_t t, void* v) {
	idsl_element_t e;

	assert (t != NULL);

	e = idsl_bstree_remove (t, v);

	if (e == NULL) {
		return NULL;
	}

	t->free_f (e);

	return t;
}

idsl_element_t 
idsl_bstree_search (const idsl_bstree_t t, idsl_compare_func_t f, void* v) {
	_idsl_bintree_t n;

	assert (t != NULL);

	n = bstree_search (ROOT(t), SENT(t), f ? f : t->comp_f, v);

	return (n == NULL) ? NULL : CONTENT (n);
}

idsl_element_t
idsl_bstree_map_prefix (const idsl_bstree_t t, idsl_map_func_t map_f, void* d) {
	assert (t != NULL);
	assert (map_f != NULL);

	return bstree_prefix_parse (ROOT(t), SENT(t), map_f, d);
}

idsl_element_t
idsl_bstree_map_infix (const idsl_bstree_t t, idsl_map_func_t map_f, void* d) {
	assert (t != NULL);
	assert (map_f != NULL);

	return bstree_infix_parse (ROOT(t), SENT(t), map_f, d);
}

idsl_element_t
idsl_bstree_map_postfix (const idsl_bstree_t t, idsl_map_func_t map_f, void* d) {
	assert (t != NULL);
	assert (map_f != NULL);

	return bstree_postfix_parse (ROOT(t), SENT(t), map_f, d);
}

void
idsl_bstree_wirte (const idsl_bstree_t t, idsl_write_func_t write_f, FILE* file, void* d) {
	assert (t != NULL);
	assert (write_f != NULL);
	assert (file != NULL);

	bstree_write (ROOT(t), SENT(t), write_f, file, d);
}

void
idsl_bstree_write_xml (const idsl_bstree_t t, idsl_write_func_t write_f, FILE* file, void* d) {
	assert (t != NULL);
	assert (file != NULL);

	fprintf (file, "<IDSL_BSTREE REF=\"%p\" NAME=\"%s\" CARD=\"%ld\">\n", (void *)t, t->name, t->card);

	bstree_write_xml (ROOT(t), SENT(t), write_f, file, d);

	fprintf (file, "</IDSL_BSTREE>\n");
}

void
idsl_bstree_dump (const idsl_bstree_t t, idsl_write_func_t write_f, FILE* file, void* d) {
	assert (t != NULL);
	assert (file != NULL);

	fprintf (file, "<IDSL_BSTREE REF=\"%p\" NAME=\"%s\" CARD=\"%ld\">\n", (void*)t, t->name, t->card);
	fprintf (file, "<IDSL_BSTREE_SENT REF=\"%p\" LEFT=\"%p\" RIGHT=\"%p\" PARENT=\"%p\"/>\n", (void*)SENT(t), (void*)LEFT(SENT(t)), (void*)RIGHT(SENT(t)), (void*)PARENT(SENT(t)));

	bstree_dump (ROOT(t), SENT(t), write_f, file, d);

	fprintf (file, "</IDSL_BSTREE>\n");
}

/**************
*  private func
**************/
static idsl_element_t
default_alloc (void *e) {
	return e;
}

static void
default_free (idsl_element_t e) {
	;
}

static long int default_comp (idsl_element_t e, void* key) {
	return 0;
}

static void
bstree_free (_idsl_bintree_t n, _idsl_bintree_t sent, idsl_free_func_t f) {
	if (n != sent) {
		bstree_free (LEFT(n), sent, f);
		bstree_free (RIGHT(n), sent, f);
		f (CONTENT(n));
		free(n);
	}
}

static ulong 
bstree_height (_idsl_bintree_t n, _idsl_bintree_t sent) {
	if (n == sent) {
		return 0UL;
	}

	if (LEFT (n) == sent && RIGHT (n) == sent) {
		return 0UL;
	}

	return (ulong) (1UL +
			IDSL_MAX (bstree_height (LEFT(n), sent),
				bstree_height (RIGHT(n), sent)));
}

static _idsl_bintree_t
bstree_search (_idsl_bintree_t root, _idsl_bintree_t sent, idsl_compare_func_t f, void* v) {
	int comp;

	while (root != sent) {
		comp = f(CONTENT(root), v);

		if (comp == 0) {
			return root;
		}

		if (comp > 0) {
			root = LEFT (root);
		} else {
			root = RIGHT (root);
		}
	}

	return NULL;
}

static _idsl_bintree_t
bstree_next (idsl_bstree_t t, _idsl_bintree_t n) {
	n = RIGHT(n);

	while (LEFT(n) != SENT(t)) {
		n = LEFT(n);
	}

	return n;
}
			
static idsl_element_t
bstree_prefix_parse (_idsl_bintree_t root, _idsl_bintree_t sent, idsl_map_func_t map_f, void* user_data) {
	if (root != sent) {
		idsl_element_t e = CONTENT (root);
		if (map_f (e, get_location (root, sent), user_data) == IDSL_MAP_STOP) {
			return e;
		}

		bstree_prefix_parse (LEFT(root), sent, map_f, user_data);
		bstree_prefix_parse (RIGHT(root), sent, map_f, user_data);
	}

	return NULL;
}

static idsl_element_t
bstree_infix_parse (_idsl_bintree_t root, _idsl_bintree_t sent, idsl_map_func_t map_f, void* user_data) {
	if (root != sent) {
		idsl_element_t e;

		bstree_infix_parse (LEFT(root), sent, map_f, user_data);

		e = CONTENT (root);
		if (map_f (e, get_location (root, sent), user_data) == IDSL_MAP_STOP) {
			return e;
		}

		bstree_infix_parse (RIGHT(root), sent, map_f, user_data);
	}

	return NULL;
}

static idsl_element_t
bstree_postfix_parse (_idsl_bintree_t root, _idsl_bintree_t sent, idsl_map_func_t map_f, void* user_data) {
	if (root != sent) {
		idsl_element_t e;

		bstree_postfix_parse (LEFT(root), sent, map_f, user_data);
		bstree_postfix_parse (RIGHT(root), sent, map_f, user_data);

		e = CONTENT (root);
		if (map_f (e, get_location(root, sent), user_data) == IDSL_MAP_STOP) {
			return e;
		}
	}

	return NULL;
}


static idsl_location_t
get_location (_idsl_bintree_t n, _idsl_bintree_t s) {
	idsl_location_t location = IDSL_LOCATION_UNDEF;

	if (PARENT (n) == s) {
		location |= IDSL_LOCATION_ROOT;
	}

	if (LEFT(n) == s && RIGHT(n) == s) {
		location |= IDSL_LOCATION_LEAF;
	}

	return location;
}

static void
bstree_write (_idsl_bintree_t n, _idsl_bintree_t sent, idsl_write_func_t write_f, FILE* file, void* d) {
	if (n != sent) {
		bstree_write (LEFT(n), sent, write_f, file, d);
		write_f (CONTENT(n), file, get_location(n, sent), d);
		bstree_write (RIGHT(n), sent, write_f, file, d);
	}
}

static void
bstree_write_xml (_idsl_bintree_t n, _idsl_bintree_t sent, idsl_write_func_t write_f, FILE* file, void* d) {
	if (n != sent) {
		bstree_write_xml (LEFT(n), sent, write_f, file, d);

		if (LEFT(n) == sent && RIGHT(n) == sent) {
			fprintf (file, "<IDSL_BSTREE_LEAF REF=\"%p\"", (void*) n);
		} else {
			fprintf (file, "<IDSL_BSTREE_NODE REF=\"%p\"", (void*) n);
		}

		if (LEFT(n) != sent || RIGHT(n) != sent) {
			if (LEFT (n) != sent) {
				fprintf (file, " LEFT=\"%p\"", (void*) LEFT(n));
			} else {
				fprintf (file, " LEFT=\"\"");
			}

			if (RIGHT (n) != sent) {
				fprintf (file, " RIGHT=\"%p\"", (void*) RIGHT(n));
			} else {
				fprintf (file, " RIGHT=\"\"");
			}
		}

		if (PARENT (n) != sent) {
			fprintf (file, " PARENT=\"%p\">", (void*) PARENT(n));
		} else {
			fprintf (file, " PARENT=\"\">");
		}

		if (write_f != NULL) {
			write_f (CONTENT(n), file, get_location (n, sent), d);
		}

		if (LEFT (n) == sent && RIGHT (n) == sent) {
			fprintf (file, "</IDSL_BSTREE_LEAF>\n");
		} else {
			fprintf (file, "</IDSL_BSTREE_NODE>\n");
		}

		bstree_write_xml (RIGHT(n), sent, write_f, file, d);
	}
}

static void
bstree_dump (_idsl_bintree_t n, _idsl_bintree_t sent, idsl_write_func_t write_f, FILE* file, void* d) {
	if (n != sent) {
		bstree_dump (LEFT(n), sent, write_f, file, d);

		if (LEFT(n) == sent && RIGHT(n) == sent) {
			fprintf (file, "</IDSL_BSTREE_LEAF REF=\"%p\"", (void*)n);
		} else {
			fprintf (file, "</IDSL_BSTREE_NODE REF=\"%p\"", (void*)n);
		}

		if (CONTENT(n) != NULL) {
			fprintf (file, " CONTENT=\"%p\"", (void*) CONTENT(n));
		} else {
			fprintf (file, " CONTENT=\"\"");
		}

		fprintf (file, " LEFT=\"%p\" RIGHT=\"%p\"", (void*) LEFT(n), (void*) RIGHT(n));

		if (PARENT(n) != NULL) {
			fprintf (file, " PARENT=\"%p\">", (void*)PARENT(n));
		} else {
			fprintf (file, " PARENT=\"\">");
		}

		if (write_f != NULL) {
			write_f (CONTENT(n), file, get_location (n, sent), d);
		}

		if (LEFT (n) == sent && RIGHT (n) == sent) {
			fprintf (file, "</IDSL_BSTREE_LEAF>\n");
		} else {
			fprintf (file, "</IDSL_BSTREE_NODE>\n");
		}

		bstree_dump (RIGHT(n), sent, write_f, file, d);
	}
}
