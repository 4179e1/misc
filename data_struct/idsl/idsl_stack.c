#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "idsl_types.h"
#include "idsl_stack.h"

#define _IDSL_STACK_DEFAULT_GROWING_FACTOR 1

struct _idsl_stack {
	char*				name;
	ulong				card;
	ulong				size;
	ulong				growing_factor;
	idsl_element_t*		nodes;

	idsl_alloc_func_t	alloc_f;
	idsl_free_func_t	free_f;
};

static idsl_element_t default_alloc(void *e);
static void default_free (idsl_element_t e);
static idsl_location_t get_location (idsl_stack_t s, int i);

idsl_stack_t idsl_stack_alloc (const char* name, idsl_alloc_func_t alloc_f, idsl_free_func_t free_f) {
	int i;
	idsl_stack_t s = NULL;
	
	s = (idsl_stack_t) malloc(sizeof(struct _idsl_stack));
	if (s == NULL) {
		fprintf (stderr, "malloc failed\n");
		return NULL;
	}

	s->growing_factor = _IDSL_STACK_DEFAULT_GROWING_FACTOR;

	s->nodes = (idsl_element_t*)malloc((1 + s->growing_factor) * sizeof (idsl_element_t));
	if (s->nodes == NULL) {
		fprintf (stderr, "malloc failed\n");
		free(s);
		return NULL;
	}

	for (i = 0; i <= s->growing_factor; i++) {
		s->nodes[i] = NULL;
	}

	s->card = 0UL;
	s->size = s->growing_factor;
	s->name = NULL;

	if (idsl_stack_set_name (s, name) == NULL) {
		free(s->nodes);
		free(s);
		return NULL;
	}

	s->alloc_f = alloc_f ? alloc_f : default_alloc;
	s->free_f = free_f? free_f : default_free;

	return s;
}

void idsl_stack_free (idsl_stack_t s) {
	assert (s != NULL);

	if (!idsl_stack_is_empty (s))
	{
		idsl_stack_flush (s);
	}
	
	free (s->nodes);
	free (s->name);
	free (s);
}

void idsl_stack_flush (idsl_stack_t s) {
	int i;

	assert (s != NULL);
	
	for (i = 1; i <= s->card; i++) {
		s->free_f (s->nodes[i]);
		s->nodes[i] = NULL;
	}

	s->card = 0UL;
}

idsl_element_t idsl_stack_get_top (idsl_stack_t s) {
	assert (s != NULL);

	return (s->nodes[s->card]);
}

idsl_element_t idsl_stack_get_bottom (idsl_stack_t s) {
	assert (s != NULL);

	return (s->nodes[1]);
}

idsl_element_t idsl_stack_push (idsl_stack_t s, void* value) {
	idsl_element_t e;

	assert (s != NULL);

	e = (s->alloc_f) (value);
	if (e == NULL) {
		return NULL;
	}

	if (s->card == s->size) {
		s->nodes = realloc (s->nodes, (1 + s->size + s->growing_factor) * sizeof (idsl_element_t));

		if (s->nodes == NULL) {
			s->free_f(e);
			return NULL;
		}

		s->size += s->growing_factor;
	}

	s->card++;
	s->nodes[s->card] = e;

	return e;
}

idsl_element_t idsl_stack_pop (idsl_stack_t s) {
	idsl_element_t e;

	assert (s != NULL);

	if (s->card == 0) {
		return NULL;
	}

	e = s->nodes[s->card];
	s->nodes[s->card] = NULL;
	s->card--;

	return e;
}

bool idsl_stack_is_empty (idsl_stack_t s) {
	assert (s != NULL);

	return ((s->card == 0) ? TRUE : FALSE);
}

idsl_stack_t idsl_stack_set_name (idsl_stack_t s, const char* name) {
	assert(s != NULL);

	if(s->name != NULL) {
		free (s->name);
		s->name = NULL;
	}

	if (name != NULL) {
		s->name = (char *) malloc ((1 + strlen (name)) * sizeof (char));
		if (s->name == NULL) {
			fprintf (stderr, "malloc failed\n");
			return NULL;
		}

		strcpy(s->name, name);
	}

	return s;
}

char *idsl_stack_get_name (idsl_stack_t s) {
	assert (s != NULL);

	return (s->name);
}

void idsl_stack_set_growing_factor (idsl_stack_t s, ulong value) {
	assert (s != NULL);
	assert (value > 0);

	s->growing_factor = value;
}

ulong idsl_stack_get_growing_factor (idsl_stack_t s) {
	assert (s != NULL);

	return s->growing_factor;
}

ulong idsl_stack_get_size (idsl_stack_t s) {
	assert (s != NULL);

	return s->size;
}

idsl_element_t idsl_stack_search (idsl_stack_t s, idsl_compare_func_t comp_f, void *user_data) {
	int i;

	assert (s != NULL);
	assert (comp_f != NULL);

	for (i = 1; i <= s->card; i++) {
		if (comp_f (s->nodes[i], user_data) == 0) {
			return s->nodes[i];
		}
	}

	return NULL;
}

idsl_element_t idsl_stack_by_positon (idsl_stack_t s, ulong position) {
	assert (s != NULL);

	if ((position > 0) && (position <= s->card)) {
		return s->nodes[position];
	}
	else {
		return NULL;
	}
}

idsl_element_t idsl_stack_map_backward (idsl_stack_t s, idsl_map_func_t map_f , void* user_data) {
	int i;

	assert (s != NULL);
	assert (map_f != NULL);

	for (i = 1; i<= s->card; i++) {
		if (map_f (s->nodes[i], get_location(s, i), user_data) == IDSL_MAP_STOP) {
			return s->nodes[i];
		}
	}

	return NULL;
}

idsl_element_t idsl_stack_map_forward (idsl_stack_t s, idsl_map_func_t map_f , void* user_data) {
	int i;

	assert (s != NULL);
	assert (map_f != NULL);

	for (i = s->card; i > 0; i--) {
		if (map_f (s->nodes[i], get_location(s, i), user_data) == IDSL_MAP_STOP) {
			return s->nodes[i];
		}
	}

	return NULL;
}

void idsl_stack_write (const idsl_stack_t s, idsl_write_func_t func, FILE *file, void* user_data) {
	int i;
	FILE *default_file = stdout;

	assert (s != NULL);
	assert (func != NULL);
	if (file != NULL) {
		default_file = file;
	}

	for (i = s->card; i > 0; i--) {
		func (s->nodes[i], default_file, get_location(s, i), user_data);
	}
}

void idsl_stack_write_xml (const idsl_stack_t s, idsl_write_func_t func, FILE *file, void* user_data) {
	int i;
	FILE *default_file = stdout;

	assert (s != NULL);

	if (file != NULL) {
		default_file = file;
	}

	fprintf (default_file, "<IDSL_STACK REF=\"%p\" NAME=\"%s\" CARD=\"%ld\" TOP=\"%p\" BOTTOM=\"%p\">\n", (void *)s, s->name, s->card, (void *)&(s->nodes[s->card]), (void *)&(s->nodes[1]));

	for (i = s->card; i > 0; i--) {
		fprintf (default_file, "<IDSL_STACK_NOD REF=\"%p\" CONTENT=\"%p\">", (void *)&(s->nodes[i]), (void *)s->nodes[i]);

		if (func && s->nodes[i]) {
			func(s->nodes[i], default_file, get_location(s, i), user_data);
		}

		fprintf (default_file, "</IDSL_STACK_NODE>\n");
	}
	
	fprintf (default_file, "</IDSL_STACK>\n");
}


/**********************
 * Private functions
 *********************/

static idsl_element_t default_alloc (void *e) {
	return e;
}

static void default_free (idsl_element_t e) {
	;
}

static idsl_location_t get_location (idsl_stack_t s, int i) {
	idsl_location_t location = IDSL_LOCATION_UNDEF;

	/* assert() not require, for it is a static func, shall never called by user */

	if (s->card == i) {
		location |= IDSL_LOCATION_TOP;
	}

	if (i == 1) {
		location |= IDSL_LOCATION_BOTTOM;
	}

	return location;
}
