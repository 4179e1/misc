#ifndef _LIST_H
#define _LIST_H

#include <stdio.h>
#include "listnode.h"
#include "base.h"

typedef struct _list List;

List *list_new (compare_func_t f);
void list_free (List *l);
void list_flush (List *l);

bool list_is_empty (List *l);
int list_get_size (List *l);
void list_set_compare_func (List *l, compare_func_t f);

void list_insert_head (List *l, void *data);
void list_insert_tail (List *l, void *data);

void *list_head (const List *l);
void *list_tail (const List *l);

void *list_delete_head (List *l);
void *list_delete_tail (List *l);
void *list_delete (List *l, void *data);

void *list_search (const List *l, const void *data);
/* postition begin from 0 */
void *list_search_by_position (const List *l, int pos);
void *list_search_max (const List *l);
void *list_search_min (const List *l);

ListNode *list_head_node (const List *l);
ListNode *list_tail_node (const List *l);
ListNode *list_search_node (const List *l, const void *data);
ListNode *list_search_node_by_position (const List *l, int pos);
ListNode *list_search_max_node (const List *l);
ListNode *list_search_min_node (const List *l);

void list_sort (List *l);

void list_dump (const List *l, FILE *file, write_func_t f);
void list_foreach (const List *l, foreach_func_t f, void *data);

#endif /* _LIST_H */
