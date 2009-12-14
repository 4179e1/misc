#include <stdio.h>
#include "treenode.h"
#include "base.h"

int main(void)
{
	TreeNode *node;
	TreeNode *p;

	
	node = tree_node_new ();
	p = tree_node_new ();

	tree_node_set_parent (node, p);

	tree_node_dump (p, stdout, NULL);
	tree_node_dump (node, stdout, NULL);
	rb_tree_node_dump (node, stdout, NULL);
	printf ("\n");

	tree_node_set_black (node);
	tree_node_dump (p, stdout, NULL);
	tree_node_dump (node, stdout, NULL);
	rb_tree_node_dump (node, stdout, NULL);
	printf ("\n");

	if (tree_node_is_black (node))
	{
		printf ("it's black\n");
	}

	tree_node_set_red (node);
	tree_node_dump (p, stdout, NULL);
	tree_node_dump (node, stdout, NULL);
	rb_tree_node_dump (node, stdout, NULL);
	printf ("\n");

	if (tree_node_is_red (node))
	{
		printf ("it's red\n");
	}

	tree_node_free (node);
	tree_node_free (p);

	return 0;
}
