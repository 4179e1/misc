#ifndef _LISTNODE_H
#define _LISTNODE_H

#include <stdio.h>
#include "base.h"

typedef struct _list_node ListNode;

ListNode *list_node_new (void);
ListNode *list_node_new_full (void *data, ListNode *p, ListNode *n);
void list_node_free (ListNode *n);

void list_node_set_content (ListNode *node, void *data);
void list_node_set_next (ListNode *node, ListNode *next);
void list_node_set_prev (ListNode *node, ListNode *prev);

void *list_node_get_content (const ListNode *node);
ListNode *list_node_get_next (const ListNode *node);
ListNode *list_node_get_prev (const ListNode *node);

void list_node_link (ListNode *prev, ListNode *next);
void list_node_unlink (ListNode *prev, ListNode *next);

void list_node_insert_before (ListNode *n, ListNode *prev);
void list_node_insert_after (ListNode *n, ListNode *next);

void list_node_dump (const ListNode *node, FILE *file, write_func_t f, void *data);

#endif /* _LIST_H */
