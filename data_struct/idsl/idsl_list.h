#ifndef _IDSL_LIST_H
#define _IDSL_LIST_H

#include <stdio.h>
#include "idsl_types.h"

typedef struct _idsl_list* idsl_list_t;

typedef struct _idsl_list_cursor* idsl_list_cursor_t;

idsl_list_t
idsl_list_alloc (const char* NAME, idsl_alloc_func_t ALLOC_F, idsl_free_func_t FREE_F);

void 
idsl_list_free (idsl_list_t L);

void 
idsl_list_flush (idsl_list_t L);

const char* 
idsl_list_get_name (const idsl_list_t L);

ulong
idsl_list_get_size (const idsl_list_t L);

bool
idsl_list_is_empty (const idsl_list_t L);

idsl_element_t
idsl_list_get_head (const idsl_list_t L);

idsl_element_t
idsl_list_get_tail (const idsl_list_t L);

idsl_list_t
idsl_list_set_name (idsl_list_t L, const char* NEW_NAME);

idsl_element_t
idsl_list_insert_head (idsl_list_t L, void* VALUE);

idsl_element_t
idsl_list_insert_tail (idsl_list_t L, void* VALUE);

idsl_element_t
idsl_list_remove_head (idsl_list_t L);

idsl_element_t
idsl_list_remove_tail (idsl_list_t L);

idsl_element_t
idsl_list_remove (idsl_list_t L, idsl_compare_func_t COMP_F, const void* VALUE);

idsl_list_t
idsl_list_delete_head (idsl_list_t L);

idsl_list_t
idsl_list_delete_tail (idsl_list_t L);

idsl_list_t
idsl_list_delete (idsl_list_t L, idsl_compare_func_t COMP_F, const void* VALUE);

idsl_element_t
idsl_list_search (const idsl_list_t L, idsl_compare_func_t COMP_F, const void* VALUE);

idsl_element_t
idsl_list_search_by_position (const idsl_list_t L, ulong POS);

idsl_element_t
idsl_list_search_max (const idsl_list_t L, idsl_compare_func_t COMP_F);

idsl_element_t
idsl_list_search_min (const idsl_list_t L, idsl_compare_func_t COMP_F);

idsl_list_t
isdl_list_sort (idsl_list_t L, idsl_compare_func_t COMP_F);

idsl_element_t
idsl_list_map_forward (const idsl_list_t L, idsl_map_func_t MAP_F, void* USER_DATA);

idsl_element_t
idsl_list_map_backward (const idsl_list_t L, idsl_map_func_t MAP_F, void* USER_DATA);

void
idsl_list_write (const idsl_list_t L, idsl_write_func_t WRITE_F, FILE* OUTPUT_FILE, void* USER_DATA);

void
idsl_list_write_xml (const idsl_list_t L, idsl_write_func_t WRITE_F, FILE* OUTPUT_FIEL, void* USER_DATA);

void
idsl_list_dump (const idsl_list_t L, idsl_write_func_t WRITE_F, FILE* OUTPUT_FIEL, void* USER_DATA);

idsl_list_cursor_t
idsl_list_cursor_alloc (const idsl_list_t L);

void
idsl_list_cursor_free (idsl_list_cursor_t C);

void idsl_list_cursor_move_to_head (idsl_list_cursor_t C);

void idsl_list_cursor_move_to_tail (idsl_list_cursor_t C);

idsl_element_t
idsl_list_cursor_move_to_value (idsl_list_cursor_t C, idsl_compare_func_t COMP_F, void* VALUE);

idsl_element_t
idsl_list_cursor_move_to_position (idsl_list_cursor_t C, ulong POS);

void
idsl_list_cursor_step_forward (idsl_list_cursor_t C);

void
idsl_list_cursor_step_backward (idsl_list_cursor_t C);

bool
idsl_list_cursor_is_on_head (const idsl_list_cursor_t C);

bool
idsl_list_cursor_is_on_tail (const idsl_list_cursor_t C);

bool
idsl_list_cursor_has_succ (const idsl_list_cursor_t C);

bool
idsl_list_cursor_has_pred (const idsl_list_cursor_t C);

void
idsl_list_cursor_set_content (idsl_list_cursor_t C, idsl_element_t E);

idsl_element_t
idsl_list_cursor_get_content (idsl_list_cursor_t C);

idsl_element_t
idsl_list_cursor_insert_after (idsl_list_cursor_t C, void* VALUE);

idsl_element_t
idsl_list_cursor_insert_before (idsl_list_cursor_t C, void* VALUE);

idsl_element_t
idsl_list_cursor_remove (idsl_list_cursor_t C);

idsl_element_t
idsl_list_cursor_remove_after (idsl_list_cursor_t C);

idsl_element_t
idsl_list_cursor_remove_before (idsl_list_cursor_t C);

idsl_list_cursor_t
idsl_list_cursor_delete (idsl_list_cursor_t C);

idsl_list_cursor_t
idsl_list_cursor_delete_after (idsl_list_cursor_t C);

idsl_list_cursor_t
idsl_list_cursor_delete_before (idsl_list_cursor_t C);

#endif /* _IDSL_LIST_H */
