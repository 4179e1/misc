#include <stdlib.h>
#include <assert.h>
#include "treenode.h"

#define RB_TREE_MASK 0x1

struct _treenode
{
	void *content;
	/* take care this, we use the last bit of the pointer to idicate the node is red or black */
	unsigned long parent;
	TreeNode *left;
	TreeNode *right;
} __attribute__((aligned(sizeof(long))));

TreeNode *tree_node_new (void)
{
	return (TreeNode *)Calloc (1, sizeof (TreeNode));
}

TreeNode *tree_node_new_full (void *content, TreeNode *parent, TreeNode *left, TreeNode *right)
{
	TreeNode *node;

	node = (TreeNode *)Malloc (sizeof (TreeNode));
	node->content = content;
	node->parent = (unsigned long)parent;
	node->left = left;
	node->right = right;

	return node;
}

void tree_node_copy (TreeNode *dest, const TreeNode *src)
{
	assert (dest != NULL);
	assert (src != NULL);

	dest->content = src->content;
	dest->parent = src->parent;
	dest->left = src->left;
	dest->right = src->right;
}

void tree_node_free (TreeNode *node)
{
	assert (node != NULL);
	free (node);
}

void tree_node_set_content (TreeNode *node, void *data)
{
	assert (node != NULL);
	node->content = data;
}

void tree_node_set_parent (TreeNode *node, TreeNode *parent)
{
	int rb_status;
	assert (node != NULL);
	rb_status = ((node->parent) & RB_TREE_MASK);
	node->parent = (unsigned long) ((unsigned long)(parent) | rb_status);
}

void tree_node_set_left (TreeNode *node, TreeNode *left)
{
	assert (node != NULL);
	node->left = left;
}

void tree_node_set_right (TreeNode *node, TreeNode *right)
{
	assert (node != NULL);
	node->right = right;
}

void *tree_node_get_content (const TreeNode *node)
{
	assert (node != NULL);
	return node->content;
}

TreeNode *tree_node_get_parent (const TreeNode *node)
{
	assert (node != NULL);
	return (TreeNode *)((node->parent) & (~RB_TREE_MASK));
}

TreeNode *tree_node_get_left (const TreeNode *node)
{
	assert (node != NULL);
	return node->left;
}

TreeNode *tree_node_get_right (const TreeNode *node)
{
	assert (node != NULL);
	return node->right;
}

bool tree_node_is_leaf (const TreeNode *node)
{
	assert (node != NULL);
	return ((node->left == NULL) && (node->right == NULL));
}

bool tree_node_is_root (const TreeNode *node)
{
	assert (node != NULL);
	return (tree_node_get_parent (node) == NULL);
}

/* For Red-Black Tree */
void tree_node_set_red (TreeNode *node)
{
	assert (node != NULL);
	node->parent &= (~RB_TREE_BLACK);
}

void tree_node_set_black (TreeNode *node)
{
	assert (node != NULL);
	node->parent |= RB_TREE_BLACK;
}

bool tree_node_is_red (const TreeNode *node)
{
	assert (node != NULL);
	return (((node->parent) & RB_TREE_MASK ) == RB_TREE_RED);
}

bool tree_node_is_black (const TreeNode *node)
{
	assert (node != NULL);
	return (((node->parent) & RB_TREE_MASK ) == RB_TREE_BLACK);
}

RbTreeNodeColor tree_node_get_color (const TreeNode *node)
{
	assert (node != NULL);

	return (node->parent & RB_TREE_MASK);
}

void tree_node_set_color (TreeNode *node, RbTreeNodeColor color)
{
	assert (node != NULL);
	if (color == RB_TREE_RED)
	{
		node->parent &= (~RB_TREE_BLACK);
	}
	else /* color = RB_TREE_BLACK */
	{
		node->parent |= RB_TREE_BLACK;
	}
}

void tree_node_copy_color (TreeNode *dest, const TreeNode *src)
{
	tree_node_set_color (dest, tree_node_get_color (src));
}

void tree_node_dump (const TreeNode *node, FILE *file, write_func_t f)
{
	fprintf (file, "<TREE_NODE REF=\"%p\" CONTENT=\"%p\" PARENT=\"%p\" LEFT=\"%p\" RIGHT=\"%p\">", (void *)node, (void *)node->content, (void *)tree_node_get_parent (node), (void *)node->left, (void *)node->right);
	if (f)
	{
		f (node->content, file);
	}
	fprintf (file, "</TREE_NODE>\n");
}

void rb_tree_node_dump (const TreeNode *node, FILE *file, write_func_t f)
{
	fprintf (file, "<TREE_NODE TYPE=\"%s\" REF=\"%p\" CONTENT=\"%p\" PARENT=\"%p\" LEFT=\"%p\" RIGHT=\"%p\">",
			(tree_node_is_black (node) ? "BLACK" : "RED"), (void *)node, (void *)node->content, (void *)tree_node_get_parent (node), (void *)node->left, (void *)node->right);
	if (f)
	{
		f (node->content, file);
	}
	fprintf (file, "</TREE_NODE>\n");
}

