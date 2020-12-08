#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct _tree_node TreeNode;

struct _tree_node
{
	int identifier;
	TreeNode *parent;
	TreeNode *left;
	TreeNode *right;
	void *data;
};

int identifier_from_string (const char *str)
{
	int i;
	char *ptr = (char *)&i;

	*ptr++ = *str++;
	*ptr++ = *str++;
	*ptr++ = *str++;
	*ptr = *str;

	return i;
}

bool is_tree_node (TreeNode *n)
{
	return (bool)(n->identifier == identifier_from_string ("TRND"));
}

TreeNode *tree_node_new_full (TreeNode *p, TreeNode *l, TreeNode *r, void *data)
{
	TreeNode *n;

	n = (TreeNode *) malloc (sizeof (TreeNode));
	if (n == NULL)
	{
		return NULL;
	}

	n->identifier = identifier_from_string ("TRND");
	n->parent = p;
	n->left = l;
	n->right = r;
	n->data = data;
	
	return n;
}

void tree_node_free (TreeNode *n)
{
	assert (n != NULL);
	assert (is_tree_node (n));
	free (n);
}

int main (void)
{
	TreeNode *n;
	TreeNode *no_such_node;

	n = tree_node_new_full (NULL, NULL, NULL, NULL);
	tree_node_free (n);

	tree_node_free (no_such_node); /* error */

	return 0;
}
