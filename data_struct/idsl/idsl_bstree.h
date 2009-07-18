#ifndef _IDSL_BSTREE_H
#define _IDSL_BSTREE_H

#include "idsl_types.h"

typedef struct idsl_bstree* idsl_bstree_t;

idsl_bstree_t idsl_bstree_alloc (const char* NAME, idsl_alloc_func_t ALLOC_F, idsl_free_func_t FREE_F, idsl_compare_func_t COMP_F);
void idsl_bstree_free (idsl_bstree_t T);
void idsl_bstree_flush (idsl_bstree_t T);

const char* idsl_bstree_get_name (const idsl_bstree_t T);

bool idsl_bstree_is_empty (const idsl_bstree_t T);

idsl_element_t idsl_bstree_get_root (const idsl_bstree_t T);
ulong idsl_bstree_get_size (const idsl_bstree_t T);
ulong idsl_bstree_get_height (const idsl_bstree_t T);

idsl_bstree_t idsl_bstree_set_name (idsl_bstree_t T, const char* NEW_NAME);
idsl_element_t idsl_bstree_insert (idsl_bstree_t T, void* VALUE, int* RESULT);
idsl_element_t idsl_bstree_remove (idsl_bstree_t T, void* VALUE); /* the element need to be freed */
idsl_bstree_t idsl_bstree_delete (idsl_bstree_t T, void* VALUE);
idsl_element_t idsl_bstree_search (const idsl_bstree_t T, idsl_conmpare_func_t COMP_F, void* VALUE);

idsl_element_t idsl_bstree_map_prefix (const idsl_bstree_t T, idsl_map_func_t MAP_F, void* USER_DATA);
idsl_element_t idsl_bstree_map_infix (const idsl_bstree_t T, idsl_map_func_t MAP_F, void* USER_DATA);
idsl_element_t idsl_bstree_map_postfix (const idsl_bstree_t T, idsl_map_func_t MAP_F, void* USER_DATA);

void idsl_bstree_write (const idsl_bstree_t T, idsl_write_func_t WRITE_F, FILE* OUTPUT_FILE, void* USER_DATA);
void idsl_bstree_write_xml (const idsl_bstree_t T, idsl_write_func_t WRITE_F, FILE* OUTPUT_FIEL, void* USER_DATA);
void idsl_bstree_dump (const idsl_bstree_t T, idsl_write_func_t WRITE_F, FILE* OUTPUT_FILE, void* USER_DATA);

#endif /* _IDSL_BSTREE_H */
