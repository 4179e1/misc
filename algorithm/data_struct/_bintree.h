#ifndef __BINTREE_H
#define __BINTREE_H

#include <stdio.h>
#include "treenode.h"
#include "base.h"

typedef enum _bin_tree_type
{
	BIN_TREE = 0,
	RB_TREE,
} BinTreeType;

TreeNode *_bin_tree_new (void);
void _bin_tree_free (TreeNode *n, TreeNode *sent);

void _bin_tree_insert_left (TreeNode *p, TreeNode *l);
void _bin_tree_insert_right (TreeNode *p, TreeNode *r);

int _bin_tree_height (TreeNode *n, TreeNode *sent);
TreeNode *_bin_tree_search (TreeNode *n, TreeNode *sent, compare_func_t f, void *data);

TreeNode *_bin_tree_minimum (TreeNode *n, TreeNode *sent);
TreeNode *_bin_tree_maximum (TreeNode *n, TreeNode *sent);

TreeNode *_bin_tree_successor (TreeNode *n, TreeNode *sent);
TreeNode *_bin_tree_predecessor (TreeNode *n, TreeNode *sent);

void _bin_tree_map_prefix (TreeNode *n, TreeNode *sent, FILE *file, write_func_t f, void *data);
void _bin_tree_map_infix (TreeNode *n, TreeNode *sent, FILE *file, write_func_t f, void *data);
void _bin_tree_map_postfix (TreeNode *n, TreeNode *sent, FILE *file, write_func_t f, void *data);

void _bin_tree_flush (TreeNode *n, TreeNode *sent);
void _bin_tree_dump (TreeNode *n, TreeNode *sent, FILE *file, write_func_t f, void *data, BinTreeType type);
void _bin_tree_foreach (TreeNode *n, TreeNode *sent, foreach_func_t f, void *data);

#endif /* __BINTREE_H */
