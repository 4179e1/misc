#ifndef _IDSL_STACK_H
#define _IDSL_STACK_H

#include "idsl_types.h"

typedef struct _idsl_stack* idsl_stack_t;

idsl_stack_t idsl_stack_alloc (const char* NAME,
							   idsl_alloc_func_t ALLOC_F,
							   idsl_free_func_t FREE_F);

void idsl_stack_free (idsl_stack_t S);
void idsl_stack_flush (idsl_stack_t S);
bool idsl_stack_is_empty (const idsl_stack_t S);

idsl_element_t idsl_stack_get_top (idsl_stack_t S);
idsl_element_t idsl_stack_get_bottom (idsl_stack_t S);

idsl_element_t idsl_stack_push (idsl_stack_t S, void *USER_DATA);
/* the returned idls_element_t need to be free */
idsl_element_t idsl_stack_pop (idsl_stack_t S);

idsl_stack_t idsl_stack_set_name (idsl_stack_t S, const char* NEW_NAME);
char* idsl_stack_get_name (idsl_stack_t S);

void idsl_stack_set_growing_factor (idsl_stack_t S, ulong value); 
ulong idsl_stack_get_growing_factor (idsl_stack_t S);

ulong idsl_stack_get_size (idsl_stack_t S);

idsl_element_t idsl_stack_search (idsl_stack_t S, idsl_compare_func_t f, void *user_data);
idsl_element_t idsl_stack_by_positon (idsl_stack_t s, ulong position);

idsl_element_t idsl_stack_map_backward (idsl_stack_t s, idsl_map_func_t map_f, void* user_data);
idsl_element_t idsl_stack_map_forward (idsl_stack_t s, idsl_map_func_t map_f, void* user_data);

void idsl_stack_write (const idsl_stack_t s, idsl_write_func_t func, FILE *file, void* user_data);
void idsl_stack_write_xml (const idsl_stack_t s, idsl_write_func_t func, FILE *file, void* user_data);

#endif /* _IDSL_STACK_H */
