#ifndef _BINTREE_H
#define _BINTREE_H

#include <stdio.h>
#include <stdbool.h>
#include "base.h"

typedef struct _bintree BinTree;

BinTree *bin_tree_new (compare_func_t cmp_f);
void bin_tree_free (BinTree *t);
void bin_tree_flush (BinTree *t);

bool bin_tree_is_empty (const BinTree *t);
int bin_tree_get_card (const BinTree *t);
int bin_tree_get_height (const BinTree *t);

void *bin_tree_get_root (const BinTree *t);
void *bin_tree_get_minimum (const BinTree *t);
void *bin_tree_get_maximum (const BinTree *t);

void bin_tree_insert (BinTree *t, void *data);
void *bin_tree_search (const BinTree *t, void *data);
void *bin_tree_delete (BinTree *t, void *data);

void bin_tree_map_prefix (const BinTree *t, FILE *file, write_func_t f, void *data);
void bin_tree_map_infix (const BinTree *t, FILE *file, write_func_t f, void *data);
void bin_tree_map_postfix (const BinTree *t, FILE *file, write_func_t f, void *data);

void bin_tree_dump (const BinTree *t, FILE *file, write_func_t f, void *data);
void bin_tree_foreach (BinTree *t, foreach_func_t f, void *data);

#endif /* _BINTREE_H */
