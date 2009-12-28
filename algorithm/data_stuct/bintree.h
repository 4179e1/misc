#ifndef _BINTREE_H
#define _BINTREE_H

#include "bash.h"

typedef struct _bintree BinTree;

BinTree *bin_tree_new (compare_func_t cmp_f);
void bin_tree_free (BinTree *t);
void bin_tree_flush (BinTree *t);

int bin_tree_get_card (const BinTree *t);
int bin_tree_get_height (const BinTree *t);

void *bin_tree_get_root (const BinTree *t);
void *bin_tree_get_minimum (const Bintree *t);
void *bin_tree_get_maximum (const Bintree *t);

void bin_tree_insert (BinTree *t, void *data);
void *bin_tree_search (const BinTree *t, void *data);
void *bin_tree_delete (BinTree *t, void *data);

void bin_tree_map_prefix (const BinTree *t, write_func_t f, FILE *file);
void bin_tree_map_infix (const BinTree *t, write_func_t f, FILE *file);
void bin_tree_map_postfix (const BinTree *t, write_func_t f, FILE *file);

void bin_tree_dump (const BinTree *t, FILE *file, write_func_t f);
void bin_tree_foreach (BinTree *t, foreach_func_t f, void *data);

#endif /* _BINTREE_H */
