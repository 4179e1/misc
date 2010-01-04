#include <stdio.h>
#include <assert.h>
#include "_bintree.h"
#include "base.h"

#define USE_JUMP_TABLE

#ifdef USE_JUMP_TABLE
typedef void (*tree_node_dump_func)(const TreeNode *node, FILE *file, write_func_t write_f);

tree_node_dump_func action[] =
{
	tree_node_dump,		/* BIN_TREE */
	rb_tree_node_dump,	/* RB_TREE */
};

#endif /* USE_JUMP_TABLE */

TreeNode *_bin_tree_new (void)
{
	return tree_node_new_full (NULL, NULL, NULL, NULL);
}

void _bin_tree_free (TreeNode *n, TreeNode *sent)
{
	assert (n != NULL);
	_bin_tree_flush (n, sent);
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

int _bin_tree_height (TreeNode *n, TreeNode *sent)
{
	int l, r;

	if (n == sent)
	{
		return 0;
	}

	l = _bin_tree_height (tree_node_get_left (n), sent);
	r = _bin_tree_height (tree_node_get_right (n), sent);

	return (MAX (l, r) + 1);
}

TreeNode *_bin_tree_search (TreeNode *n, TreeNode *sent, compare_func_t f, void *data)
{
	int i;
	while ((n != sent) && ((i = f (data, tree_node_get_content (n))) != 0))
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

TreeNode *_bin_tree_minimum (TreeNode *n, TreeNode *sent)
{
	TreeNode *tmp;
	while ((tmp = tree_node_get_left (n)) != sent)
	{
		n = tmp;
	}
	return n;
}

TreeNode *_bin_tree_maximum (TreeNode *n, TreeNode *sent)
{
	TreeNode *tmp;
	while ((tmp = tree_node_get_right (n)) != sent)
	{
		n = tmp;
	}
	return n;
}

TreeNode *_bin_tree_successor (TreeNode *n, TreeNode *sent)
{
	TreeNode *r;
	TreeNode *y;

	if ((r = tree_node_get_right (n)) != sent)
	{
		return (_bin_tree_minimum (r, sent));
	}

	y = tree_node_get_parent (n);
	while ((y != sent) && (n == tree_node_get_right (y)))
	{
		n = y;
		y = tree_node_get_parent (y);
	}

	return y;
}
				
TreeNode *_bin_tree_predecessor (TreeNode *n, TreeNode *sent)
{
	TreeNode *l;
	TreeNode *y;
	
	if ((l = tree_node_get_left (n)) != sent)
	{
		return (_bin_tree_maximum (l, sent));
	}

	y = tree_node_get_parent (n);
	while ((y != sent) && (n == tree_node_get_left (y)))
	{
		n = y;
		y = tree_node_get_parent (y);
	}

	return y;
}

void _bin_tree_map_prefix (TreeNode *n, TreeNode *sent, FILE *file, write_func_t f)
{
	if (n != sent)
	{
		f (tree_node_get_content (n), file);
		_bin_tree_map_prefix (tree_node_get_left (n), sent, file, f);
		_bin_tree_map_prefix (tree_node_get_right (n), sent, file, f);
	}
}

void _bin_tree_map_infix (TreeNode *n, TreeNode *sent, FILE *file, write_func_t f)
{
	if (n != sent)
	{
		_bin_tree_map_infix (tree_node_get_left (n), sent, file, f);
		f (tree_node_get_content (n), file);
		_bin_tree_map_infix (tree_node_get_right (n), sent, file, f);
	}
}

void _bin_tree_map_postfix (TreeNode *n, TreeNode *sent, FILE *file, write_func_t f)
{
	if (n != sent)
	{
		_bin_tree_map_postfix (tree_node_get_left (n), sent, file, f);
		_bin_tree_map_postfix (tree_node_get_right (n), sent, file, f);
		f (tree_node_get_content (n), file);
	}
}

void _bin_tree_flush (TreeNode *n, TreeNode *sent)
{
	if (n != sent)
	{
		_bin_tree_flush (tree_node_get_left (n), sent);
		_bin_tree_flush (tree_node_get_right (n), sent);
		tree_node_free (n);
	}
}

void _bin_tree_dump (TreeNode *n, TreeNode *sent, FILE *file, write_func_t f, BinTreeType type)
{
	if (n != sent)
	{
		_bin_tree_dump (tree_node_get_left (n), sent, file, f, type);

#if defined USE_JUMP_TABLE
		action[type](n, file, f);
#else
		switch (type)
		{
			case BIN_TREE:
				tree_node_dump (n, file, f);
				break;
			case RB_TREE:
				rb_tree_node_dump (n, file, f);
				break;
			default:
				fprintf (stderr, "oops! not such tree\n");
				break;
		}
#endif /* USE_JUMP_TABLE */
		_bin_tree_dump (tree_node_get_right (n), sent, file, f, type);
	}
}

void _bin_tree_foreach (TreeNode *n, TreeNode *sent, foreach_func_t f, void *data)
{
	if (n != sent)
	{
		if (f (tree_node_get_content, data) == false)
		{
			return;
		}
		_bin_tree_foreach (tree_node_get_left (n), sent, f, data);
		_bin_tree_foreach (tree_node_get_right (n), sent, f, data);
	}
}
