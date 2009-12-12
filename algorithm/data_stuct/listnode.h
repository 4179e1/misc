#ifndef _LISTNODE_H
#define _LISTNODE_H

#include <stdio.h>
#include "base.h"

typedef struct _list_node ListNode;

ListNode *list_node_new (void);
void list_node_free (ListNode *n);

void list_node_set_content (ListNode *node, void *data);
void list_node_set_next (ListNode *node, ListNode *next);
void list_node_set_prev (ListNode *node, ListNode *prev);

void *list_node_get_content (ListNode *node);
ListNode *list_node_get_next (ListNode *node);
ListNode *list_node_get_prev (ListNode *node);

void list_node_link (ListNode *prev, ListNode *next);
void list_node_unlink (ListNode *prev, ListNode *next);

void list_node_dump (ListNode *node, FILE *file, write_func_t f);

#endif /* _LIST_H */
