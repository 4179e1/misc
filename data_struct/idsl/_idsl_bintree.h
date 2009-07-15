#ifndef __IDSL_BINTREE_H
#define __IDSL_BINTREE_H

#include "idsl_types.h"

typedef struct _idsl_bintree* _idsl_bintree_t;

typedef int (* _idsl_bintree_map_func_t)
(const _idsl_bintree_t TREE, void* USER_DATA);

typedef void (* _idsl_bintree_write_func_t)
(const _idsl_bintree_t TREE, FILE* OUTPUT_FILE, void* USER_DATA);


_idsl_bintree_t _idsl_bintree_alloc (const idsl_element_t E, const _idsl_bintree_t LEFT, const _idsl_bintree_t RIGHT);
void _idsl_bintree_free (_idsl_bintree_t T, const idsl_free_func_t FREE_F);

_idsl_bintree_t _idsl_bintree_copy (const _idsl_bintree_t T, const idsl_copy_func_t COPY_F);

bool _idsl_bintree_is_empty (const _idsl_bintree_t T);
bool _idsl_bintree_is_leaf (const _idsl_bintree_t T);
bool _idsl_bintree_is_root (const _idsl_bintree_t T);

idsl_element_t _idsl_bintree_get_content (const _idsl_bintree_t T);
_idsl_bintree_t _idsl_bintree_get_parent (const _idsl_bintree_t T);
_idsl_bintree_t _idsl_bintree_get_left (const _idsl_bintree_t T);
_idsl_bintree_t _idsl_bintree_get_right (const _idsl_bintree_t T);
_idsl_bintree_t* _idsl_bintree_get_left_ref (const _idsl_bintree_t T);
_idsl_bintree_t* _idsl_bintree_get_right_ref (const _idsl_bintree_t T);
ulong _idsl_bintree_get_height (const _idsl_bintree_t T);
ulong _idsl_bintree_get_size (const _idsl_bintree_t T);

void _idsl_bintree_set_content (_idsl_bintree_t T, const idsl_element_t E);
void _idsl_bintree_set_parent (_idsl_bintree_t T, const _idsl_bintree_t P);
void _idsl_bintree_set_left (_idsl_bintree_t T, const _idsl_bintree_t L);
void _idsl_bintree_set_right (_idsl_bintree_t T, const _idsl_bintree_t R);

_idsl_bintree_t _idsl_bintree_rotate_left (_idsl_bintree_t* T);
_idsl_bintree_t _idsl_bintree_rotate_right (_idsl_bintree_t* T);
_idsl_bintree_t _idsl_bintree_rotate_left_right (_idsl_bintree_t* T);
_idsl_bintree_t _idsl_bintree_roate_right_left (_idsl_bintree_t* T);

_idsl_bintree_t _idsl_bintree_map_prefix (const _idsl_bintree_t T, const _idsl_bintree_map_func_t MAP_F, void* USER_DATA);
_idsl_bintree_t _idsl_bintree_map_infix (const _idsl_bintree_t T, const _idsl_bintree_map_func_t MAP_F, void* USER_DATA);
_idsl_bintree_t _idsl_bintree_map_postfix (const _idsl_bintree_t T, const _idsl_bintree_map_func_t MAP_F, void* USER_DATA);

void _idsl_bintree_write (const _idsl_bintree_t T, const _idsl_bintree_write_func_t WRITE_F, FILE* OUTPUT_FILE, void* USER_DATA);
void _idsl_bintree_write_xml (const _idsl_bintree_t T, const _idsl_bintree_write_func_t WRITE_F, FILE* OUTPUT_FILE, void* USER_DATA);
void _idsl_bintree_dump (const _idsl_bintree_t T, const _idsl_bintree_write_func_t WIRTE_F, FILE* OUTPUT_FILE, void* USER_DATA);
#endif /* __IDSL_BINTREE_H */
