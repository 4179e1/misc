#ifndef _TREENODE_H
#define _TREENODE_H

#include <stdio.h>
#include <stdbool.h>
#include "base.h"

typedef struct _treenode TreeNode;

TreeNode *tree_node_new (void);
TreeNode *tree_node_new_full (void *content, TreeNode *parent, TreeNode *left, TreeNode *right);
void tree_node_free (TreeNode *node);

void tree_node_set_content (TreeNode *node, void *data);
void tree_node_set_parent (TreeNode *node, TreeNode *parent);
void tree_node_set_left (TreeNode *node, TreeNode *left);
void tree_node_set_right (TreeNode *node, TreeNode *right);

void *tree_node_get_content (const TreeNode *node);
TreeNode *tree_node_get_parent (const TreeNode *node);
TreeNode *tree_node_get_left (const TreeNode *node);
TreeNode *tree_node_get_right (const TreeNode *node);

bool tree_node_is_leaf (const TreeNode *node);
bool tree_node_is_root (const TreeNode *node);

/* For Red-Black Tree */
void tree_node_set_red (TreeNode *node);
void tree_node_set_black (TreeNode *node);
bool tree_node_is_red (const TreeNode *node);
bool tree_node_is_black (const TreeNode *node);

void tree_node_dump (const TreeNode *node, FILE *file, write_func_t f);
void rb_tree_node_dump (const TreeNode *node, FILE *file, write_func_t f);

#endif /* _TREENODE_H */
