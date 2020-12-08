#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "_idsl_node.h"
#include "idsl_types.h"

struct _idsl_node
{
	struct _idsl_node* succ;
	struct _idsl_node* pred;
	idsl_element_t content;
};

_idsl_node_t
_idsl_node_alloc (void) {
	_idsl_node_t n;

	n = (_idsl_node_t) malloc (sizeof (struct _idsl_node));
	if (n == NULL) {
		return NULL;
	}

	n->content = NULL;
	n->succ = NULL;
	n->pred = NULL;

	return n;
}

idsl_element_t
_idsl_node_free (_idsl_node_t n) {
	idsl_element_t e;

	assert (n != NULL);

	e = n->content;
	free (n);

	return e;
}

_idsl_node_t
_idsl_node_get_succ (const _idsl_node_t n) {
	assert (n != NULL);

	return n->succ;
}

_idsl_node_t
_idsl_node_get_pred (const _idsl_node_t n) {
	assert (n != NULL);

	return n->pred;
}

idsl_element_t
_idsl_node_get_content (const _idsl_node_t n) {
	assert (n != NULL);

	return n->content;
}

void
_idsl_node_set_succ (_idsl_node_t n, const _idsl_node_t succ) {
	assert (n != NULL);

	n->succ = succ;
}

void
_idsl_node_set_pred (_idsl_node_t n, const _idsl_node_t pred) {
	assert (n != NULL);

	n->pred = pred;
}

void
_idsl_node_set_content (_idsl_node_t n, const idsl_element_t e) {
	assert (n != NULL);

	n->content = e;
}

void
_idsl_node_link (_idsl_node_t node1, _idsl_node_t node2) {
	assert (node1 != NULL);
	assert (node2 != NULL);

	node1->succ = node2;
	node2->pred = node1;
}

void
_idsl_node_unlink (_idsl_node_t node1, _idsl_node_t node2) {
	assert (node1 != NULL);
	assert (node2 != NULL);

	node1->succ = NULL;
	node2->pred = NULL;
}

void
_idsl_node_write (const _idsl_node_t n, const _idsl_node_write_func_t write_f, FILE* file, void* user_data) {
	assert (n != NULL);
	assert (write_f != NULL);
	assert (file != NULL);

	write_f (n, file, user_data);
}

void
_idsl_node_write_xml (const _idsl_node_t n, const _idsl_node_write_func_t write_f, FILE* file, void* user_data) {
	assert (n != NULL);
	assert (file != NULL);

	fprintf (file, "<_IDSL_NODE REF=\"%p\"", (void*) n);

	if (n->succ != NULL) {
		fprintf (file, " SUCC=\"%p\"", (void*)n->succ);
	} else {
		fprintf (file, " SICC=\"\"");
	}

	if (n->pred != NULL) {
		fprintf (file, " PRED=\"%p\"", (void*)n->pred);
	} else {
		fprintf (file, " PRED=\"\"");
	}

	if (write_f != NULL) {
		write_f (n, file, user_data);
	}

	fprintf (file, "</_IDSL_NODE>\n");
}

void
_idsl_node_dump (const _idsl_node_t n, const _idsl_node_write_func_t write_f, FILE* file, void* user_data) {
	assert (n != NULL);
	assert (file != NULL);

	fprintf (file, "<_IDSL_NODE REF=\"%p\"", (void*) n);

	if (n->content != NULL) {
		fprintf (file, " CONTENT=\"%p\"", (void*)n->content);
	} else {
		fprintf (file, " CONTENT=\"\"");
	}

	if (n->succ != NULL) {
		fprintf (file, " SUCC=\"%p\"", (void*) n->succ);
	} else {
		fprintf (file, " SUCC=\"\"");
	}

	if (n->pred != NULL) {
		fprintf (file, " PRED=\"%p\"", (void*) n->pred);
	} else {
		fprintf (file, " PRED=\"\"");
	}

	if (write_f != NULL) {
		write_f (n, file, user_data);
	}

	fprintf (file, "</_IDSL_NODE>\n");
}
				
