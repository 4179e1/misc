#ifndef _TREENODE_H
#define _TREENODE_H

#include <stdio.h>
#include "base.h"

typedef struct _treenode TreeNode;

TreeNode *tree_node_new (void);
TreeNode *tree_node_new_with_param (void *content, TreeNode *parent, TreeNode *left, TreeNode *right);
void tree_node_free (TreeNode *node);

void tree_node_set_content (TreeNode *node, void *data);
void tree_node_set_parent (TreeNode *node, TreeNode *parent);
void tree_node_set_left (TreeNode *node, TreeNode *left);
void tree_node_set_right (TreeNode *node, TreeNode *right);

void *tree_node_get_content (const TreeNode *node);
TreeNode *tree_node_get_parent (const TreeNode *node);
TreeNode *tree_node_get_left (const TreeNode *node);
TreeNode *tree_node_get_right (const TreeNode *node);

void tree_node_dump (const TreeNode *node, FILE *file, write_func_t f);

#endif /* _TREENODE_H */
