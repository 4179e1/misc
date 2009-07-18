#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "idsl_types.h"
#include "_idsl_bintree.h"
#include "idsl_bstree.h"

#define LEFT(t)		( _idsl_bintree_get_left ((t)) )
#define RIGHT(t)	( _idsl_bintree_get_right ((t)) )
#define CONTENT(t)	( _idsl_bintree_get_content ((t)) )
#define PARENT(t)	( _idsl_bintree_get_parent ((t)) )
#define SENT(t)		( (t)->sent )
#define ROOT(t)		( _idsl_bintree_get_RIGHT (SENT(t)))

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
bstree_next (_idsl_bintree_t t, _idsl_bintree_t n);

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
bstree_dump (_idsl_bintree_t n, _idsl_bintree_t sent, idsl_wirte_func_t f, FILE* file, void* d);

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