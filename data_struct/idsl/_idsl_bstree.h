#ifndef __IDSL_BSTREE_H
#define __IDSL_BSTREE_H

#include "idsl_types.h"
#include "idsl_macros.h"
#include "_idsl_bintree.h"

typedef _idsl_bintree_t _idsl_bstree_t;

typedef int (* _idsl_bstree_map_func_t) (_idsl_bstree_t TREE, void *USER_DATA);

typedef void (* _idsl_bstree_write_func_t) (_idsl_bstree_t TREE, FILE* OUTPUT_FILE, void* USER_DATA);

_idsl_bstree_t _idsl_bstree_alloc (const idsl_element_t E);
void _idsl_bstree_free (_idsl_bstree_t T, const idsl_free_func_t FREE_F);

_idsl_bstree_t _idsl_bstree_copy (const _idsl_bstree_t T, const idsl_copy_func_t COPY_F);

bool _idsl_bstree_is_empty (const _idsl_bstree_t T);
bool _idsl_bstree_is_leaf (const _idsl_bstree_t T);
bool _idsl_bstree_is_root (const _idsl_bstree_t T);

idsl_element_t _idsl_bstree_get_content (const _idsl_bstree_t T);
_idsl_bstree_t _idsl_bstree_get_parent (const _idsl_bstree_t T);
_idsl_bstree_t _idsl_bstree_get_left (const _idsl_bstree_t T);
_idsl_bstree_t _idsl_bstree_get_right (const _idsl_bstree_t T);

ulong _idsl_bstree_get_size (const _idsl_bstree_t T);
ulong _idsl_bstree_get_height (const _idsl_bstree_t T);

_idsl_bstree_t _idsl_bstree_insert (_idsl_bstree_t* T, const idsl_compare_func_t COMP_F, const idsl_element_t VALUE, int* RESULT);
idsl_element_t _idsl_bstree_remove (_idsl_bstree_t* T, const idsl_compare_func_t COMP_F, const idsl_element_t VALUE);

_idsl_bstree_t _idsl_bstree_search (const _idsl_bstree_t T, const idsl_compare_func_t COMP_F, const idsl_element_t VALUE);
_idsl_bstree_t _idsl_bstree_search_next (const _idsl_bstree_t T, const idsl_compare_func_t COMP_F, const idsl_element_t VALUE);

_idsl_bstree_t _idsl_bstree_map_prefix (const _idsl_bstree_t T, const _idsl_bstree_map_func_t MAP_F, void* USER_DATA);
_idsl_bstree_t _idsl_bstree_map_infix (const _idsl_bstree_t T, const _idsl_bstree_map_func_t MAP_F, void* USER_DATA);
_idsl_bstree_t _idsl_bstree_map_postfix (const _idsl_bstree_t T, const _idsl_bstree_map_func_t MAP_F, void* USER_DATA);

void _idsl_bstree_write (const _idsl_bstree_t T, const _idsl_bstree_write_func_t WRITE_F, FILE* OUTPUT_FILE, void* USER_DATA);
void _idsl_bstree_write_xml (const _idsl_bstree_t T, const _idsl_bstree_write_func_t WRITE_F, FILE* file, void* USER_DATA);
void _idsl_bstree_dump (const _idsl_bstree_t T, const _idsl_bstree_write_func_t WRITE_F, FILE* OUTPUT_FILE, void* USER_DATA);


#endif /* __IDSL_BSTREE_H */
