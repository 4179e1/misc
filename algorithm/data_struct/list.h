#ifndef _LIST_H
#define _LIST_H

#include <stdio.h>
#include "base.h"

typedef struct _list List;

typedef struct _list_cursor ListCursor;

List *list_new (compare_func_t f);
void list_free (List *l);
void list_flush (List *l);

bool list_is_empty (List *l);
int list_get_card (List *l);
void list_set_compare_func (List *l, compare_func_t f);

void list_insert_head (List *l, void *data);
void list_insert_tail (List *l, void *data);

void *list_head (List *l);
void *list_tail (List *l);

void *list_delete_head (List *l);
void *list_delete_tail (List *l);
void *list_delete (List *l, void *data);

void *list_search (List *l, void *data);
/* postition begin from 0 */
void *list_search_by_position (List *l, int pos);
void *list_search_max (List *l);
void *list_search_min (List *l);

void list_sort (List *l);

void list_dump (List *l, FILE *file, write_func_t f);
void list_foreach (List *l, foreach_func_t f, void *data);

/* List Cursor */
ListCursor *list_cursor_new (List *l);
void list_cursor_free (ListCursor *lc);

bool list_cursor_is_head (const ListCursor *lc);
bool list_cursor_is_tail (const ListCursor *lc);

void list_cursor_move_to_head (ListCursor *lc);
void list_cursor_move_to_tail (ListCursor *lc);
void list_cursor_step_forward (ListCursor *lc);
void list_cursor_step_backward (ListCursor *lc);
void *list_cursor_move_to_value (ListCursor *lc, void *value);
void *list_cursor_move_to_position (ListCursor *lc, int i);

void list_cursor_set_content (ListCursor *lc, void *data);
void *list_cursor_get_content (ListCursor *lc);

void list_cursor_insert_before (ListCursor *lc, void *data);
void list_cursor_insert_after (ListCursor *lc, void *data);
void *list_cursor_remove (ListCursor *lc);
void *list_cursor_remove_before (ListCursor *lc);
void *list_cursor_remove_after (ListCursor *lc);

#endif /* _LIST_H */
