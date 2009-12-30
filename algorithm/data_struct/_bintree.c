#include <stdio.h>
#include <assert.h>
#include "_bintree.h"
#include "base.h"

TreeNode *_bin_tree_new (void)
{
	return tree_node_new_full (NULL, NULL, NULL, NULL);
}

void _bin_tree_free (TreeNode *n)
{
	assert (n != NULL);
	_bin_tree_flush (n);
}

void _bin_tree_insert_left (TreeNode *p, TreeNode *l)
{
	assert (p != NULL);
	assert (l != NULL);
	
	tree_node_set_left (p, l);
	tree_node_set_parent (l, p);
}

void _bin_tree_insert_right (TreeNode *p, TreeNode *r)
{
	assert (p != NULL);
	assert (r != NULL);

	tree_node_set_right (p, r);
	tree_node_set_parent (r, p);
}

int _bin_tree_height (TreeNode *n)
{
	int l, r;

	if (tree_node_is_leaf (n))
	{
		return 0;
	}

	l = _bin_tree_height (tree_node_get_left (n));
	r = _bin_tree_height (tree_node_get_right (n));

	return (MAX (l, r) + 1);
}

TreeNode *_bin_tree_search (TreeNode *n, compare_func_t f, void *data)
{
	int i;
	while ((n != NULL) && ((i = f (data, tree_node_get_content (n))) != 0))
	{
		if (i < 0)
		{
			n = tree_node_get_left (n);
		}
		else
		{
			n = tree_node_get_right (n);
		}
	}
	return n;
}

TreeNode *_bin_tree_minimum (TreeNode *n)
{
	TreeNode *tmp;
	while ((tmp = tree_node_get_left (n)) != NULL)
	{
		n = tmp;
	}
	return n;
}

TreeNode *_bin_tree_maximum (TreeNode *n)
{
	TreeNode *tmp;
	while ((tmp = tree_node_get_right (n)) != NULL)
	{
		n = tmp;
	}
	return n;
}

TreeNode *_bin_tree_successor (TreeNode *n)
{
	TreeNode *r;
	TreeNode *y;

	if ((r = tree_node_get_right (n)) != NULL)
	{
		return (_bin_tree_minimum (r));
	}

	y = tree_node_get_parent (n);
	while ((y != NULL) && (n == tree_node_get_right (y)))
	{
		n = y;
		y = tree_node_get_parent (y);
	}

	return y;
}
				
TreeNode *_bin_tree_predecessor (TreeNode *n)
{
	TreeNode *l;
	TreeNode *y;
	
	if ((l = tree_node_get_left (n)) != NULL)
	{
		return (_bin_tree_maximum (l));
	}

	y = tree_node_get_parent (n);
	while ((y != NULL) && (n == tree_node_get_left (y)))
	{
		n = y;
		y = tree_node_get_parent (y);
	}

	return y;
}

void _bin_tree_map_prefix (TreeNode *n, FILE *file, write_func_t f)
{
	if (n != NULL)
	{
		f (tree_node_get_content (n), file);
		_bin_tree_map_prefix (tree_node_get_left (n), file, f);
		_bin_tree_map_prefix (tree_node_get_right (n), file, f);
	}
}

void _bin_tree_map_infix (TreeNode *n, FILE *file, write_func_t f)
{
	if (n != NULL)
	{
		_bin_tree_map_infix (tree_node_get_left (n), file, f);
		f (tree_node_get_content (n), file);
		_bin_tree_map_infix (tree_node_get_right (n), file, f);
	}
}

void _bin_tree_map_postfix (TreeNode *n, FILE *file, write_func_t f)
{
	if (n != NULL)
	{
		_bin_tree_map_postfix (tree_node_get_left (n), file, f);
		_bin_tree_map_postfix (tree_node_get_right (n), file, f);
		f (tree_node_get_content (n), file);
	}
}

void _bin_tree_flush (TreeNode *n)
{
	if (n != NULL)
	{
		_bin_tree_flush (tree_node_get_left (n));
		_bin_tree_flush (tree_node_get_right (n));
		tree_node_free (n);
	}
}

void _bin_tree_dump (TreeNode *n, FILE *file, write_func_t f)
{
	if (n != NULL)
	{
		_bin_tree_dump (tree_node_get_left (n), file, f);
		tree_node_dump (n, file, f);
		_bin_tree_dump (tree_node_get_right (n), file, f);
	}
}

void _bin_tree_foreach (TreeNode *n, foreach_func_t f, void *data)
{
	if (n != NULL)
	{
		if (f (tree_node_get_content, data) == false)
		{
			return;
		}
		_bin_tree_foreach (tree_node_get_left (n), f, data);
		_bin_tree_foreach (tree_node_get_right (n), f, data);
	}
}
