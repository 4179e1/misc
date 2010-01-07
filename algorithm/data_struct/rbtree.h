#ifndef _RBTREE_H
#define _RBTREE_H

#include <stdio.h>
#include "base.h"

typedef struct _rbtree RbTree;

RbTree *rb_tree_new (compare_func_t cmp_f);
void rb_tree_free (RbTree *t);
void rb_tree_flush (RbTree *t);

bool rb_tree_is_empty (const RbTree *t);
int rb_tree_get_card (const RbTree *t);
int rb_tree_get_height (const RbTree *t);

void *rb_tree_get_root (const RbTree *t);
void *rb_tree_get_minimum (const RbTree *t);
void *rb_tree_get_maximum (const RbTree *t);

void rb_tree_insert (RbTree *t, void *data);
void *rb_tree_search (const RbTree *t, void *data);
void *rb_tree_delete (RbTree *t, void *data);

void rb_tree_map_prefix (const RbTree *t, FILE *file, write_func_t f, void *data);
void rb_tree_map_infix (const RbTree *t, FILE *file, write_func_t f, void *data);
void rb_tree_map_postfix (const RbTree *t, FILE *file, write_func_t f, void *data);

void rb_tree_dump (const RbTree *t, FILE *file, write_func_t f, void *data);
void rb_tree_foreach (RbTree *t, foreach_func_t f, void *data);
#endif /* _RBTREE_H */
