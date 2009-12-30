#ifndef __BINTREE_H
#define __BINTREE_H

#include <stdio.h>
#include "treenode.h"
#include "base.h"

TreeNode *_bin_tree_new (void);
void _bin_tree_free (TreeNode *n);

void _bin_tree_insert_left (TreeNode *p, TreeNode *l);
void _bin_tree_insert_right (TreeNode *p, TreeNode *r);

int _bin_tree_height (TreeNode *n);
TreeNode *_bin_tree_search (TreeNode *n, compare_func_t f, void *data);

TreeNode *_bin_tree_minimum (TreeNode *n);
TreeNode *_bin_tree_maximum (TreeNode *n);

TreeNode *_bin_tree_successor (TreeNode *n);
TreeNode *_bin_tree_predecessor (TreeNode *n);

void _bin_tree_map_prefix (TreeNode *n, FILE *file, write_func_t f);
void _bin_tree_map_infix (TreeNode *n, FILE *fil, write_func_t f);
void _bin_tree_map_postfix (TreeNode *n, FILE *file, write_func_t f);

void _bin_tree_flush (TreeNode *n);
void _bin_tree_dump (TreeNode *n, FILE *file, write_func_t f);
void _bin_tree_foreach (TreeNode *n, foreach_func_t f, void *data);

#endif /* __BINTREE_H */
