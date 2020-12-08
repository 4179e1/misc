#ifndef __IDSL_LIST_H
#define __IDSL_LIST_H

#include <stdio.h>

#include "_idsl_node.h"
#include "idsl_types.h"

typedef _idsl_node_t _idsl_list_t;

_idsl_list_t
_idsl_list_alloc (const idsl_element_t E);

void
_idsl_list_free (_idsl_list_t L, const idsl_free_func_t FREE_F);

bool
_idsl_list_is_empty (const _idsl_list_t L);

ulong 
_idsl_list_get_size (const _idsl_list_t L);

void
_idsl_list_link (_idsl_list_t L1, _idsl_list_t L2);

void
_idsl_list_insert_after (_idsl_list_t L, _idsl_list_t PREV);

void
_idsl_list_insert_before (_idsl_list_t L, _idsl_list_t SUCC);

void
_idsl_list_remove (_idsl_node_t NODE);

_idsl_list_t
_idsl_list_search (_idsl_list_t L, const idsl_compare_func_t COMP_F, void* VALUE);

_idsl_list_t
_idsl_list_map_forward (const _idsl_list_t L, const _idsl_node_map_func_t MAP_F, void* USER_DATA);

_idsl_list_t
_idsl_list_map_backward (const _idsl_list_t L, const _idsl_node_map_func_t MAP_F, void* USER_DATA);

void
_idsl_list_write (const _idsl_list_t L, const _idsl_node_write_func_t WRITE_F, FILE* OUTPUT_FILE, void* USER_DATA);

void
_idsl_list_write_xml (const _idsl_list_t L, const _idsl_node_write_func_t WRITE_F, FILE* OUTPUT_FILE, void* USER_DATA);

void
_idsl_list_dump (const _idsl_list_t L, const _idsl_node_write_func_t WRITE_F, FILE* OUTPUT_FILE, void* USER_DATA);

#endif /* __IDSL_LISTH_H */
