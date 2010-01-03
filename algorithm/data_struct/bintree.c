#include <assert.h>
#include <stdlib.h>
#include "_bintree.h"
#include "bintree.h"
#include "treenode.h"

struct _bintree
{
	TreeNode *sent;
	int card;
	compare_func_t cmp_f;
};

BinTree *bin_tree_new (compare_func_t cmp_f)
{
	BinTree *t;

	assert (cmp_f != NULL);

	t = (BinTree *)Malloc (sizeof (BinTree));
	if (t == NULL)
	{
		return NULL;
	}

	t->sent = tree_node_new_full (NULL, NULL, NULL, NULL);
	if (t->sent == NULL)
	{
		free (t);
		return NULL;
	}

	t->card = 0;
	t->cmp_f = cmp_f;

	return t;
}

void bin_tree_free (BinTree *t)
{
	assert (t != NULL);

	bin_tree_flush (t);
	free (t->sent);
	free (t);
}

void bin_tree_flush (BinTree *t)
{
	assert (t != NULL);

	_bin_tree_flush (tree_node_get_right (t->sent), NULL);
	tree_node_set_right (t->sent, NULL);
	t->card = 0;
}

bool bin_tree_is_empty (const BinTree *t)
{
	assert (t != NULL);
	return (t->card == 0);
}

int bin_tree_get_card (const BinTree *t)
{
	assert (t != NULL);
	return t->card;
}

int bin_tree_get_height (const BinTree *t)
{
	assert (t != NULL);

	return _bin_tree_height (tree_node_get_right (t->sent), NULL);
}

void *bin_tree_get_root (const BinTree *t)
{
	assert (t != NULL);

	return tree_node_get_content (tree_node_get_right (t->sent));
}

void *bin_tree_get_minimum (const BinTree *t)
{
	assert (t != NULL);

	return tree_node_get_content (_bin_tree_minimum (tree_node_get_right (t->sent), NULL));
}

void *bin_tree_get_maximum (const BinTree *t)
{
	assert (t != NULL);

	return tree_node_get_content (_bin_tree_maximum (tree_node_get_right (t->sent), NULL));
}

void bin_tree_insert (BinTree *t, void *data)
{
	TreeNode *y;
	TreeNode *x;
	TreeNode *tmp;

	assert (t != NULL);

	tmp = tree_node_new_full (data, NULL, NULL, NULL);
	if (tmp == NULL)
	{
		return;
	}

	y = NULL;
	x = tree_node_get_right (t->sent);

	while (x != NULL)
	{
		y = x;
		if (t->cmp_f (data, tree_node_get_content (x)) < 0)
		{
			x = tree_node_get_left (x);
		}
		else
		{
			x = tree_node_get_right (x);
		}
	}

	tree_node_set_parent (tmp, y);

	if (y == NULL)
	{
		tree_node_set_right (t->sent, tmp);	/* t is empty */
	}
	else
	{
		if (t->cmp_f (data, tree_node_get_content (y)) < 0)
		{
			tree_node_set_left (y, tmp);
		}
		else
		{
			tree_node_set_right (y, tmp);
		}
	}

	(t->card)++;
}

void *bin_tree_search (const BinTree *t, void *data)
{
	TreeNode *tmp;
	assert (t != NULL);

	tmp = _bin_tree_search (tree_node_get_right (t->sent), NULL, t->cmp_f, data);

	if (tmp == NULL)
	{
		return NULL;
	}

	return tree_node_get_content (tmp);
}

void *bin_tree_delete (BinTree *t, void *data)
{
	TreeNode *x;	/* y's not NULL child, or NULL if y don't have child */
	TreeNode *y;	/* the node actually delete */
	TreeNode *z;	/* the node contain data */
	TreeNode *py;	/* parent of y */

	assert (t != NULL);

	z = _bin_tree_search (tree_node_get_right (t->sent), NULL, t->cmp_f, data);
	if (z == NULL)
	{
		return NULL;
	}

	if ((tree_node_get_left (z) == NULL) || (tree_node_get_right (z) == NULL))
	{
		y = z;
	}
	else
	{
		y = _bin_tree_successor (z, NULL);
	}

	if (tree_node_get_left (y) != NULL)
	{
		x = tree_node_get_left (y);
	}
	else
	{
		x = tree_node_get_right (y);
	}

	py = tree_node_get_parent (y);

	if (x != NULL)
	{
		tree_node_set_parent (x, py);
	}

	if (py == NULL)
	{
		tree_node_set_right (t->sent, x);
	}
	else
	{
		if (y == tree_node_get_left (py))
		{
			tree_node_set_left (py, x);
		}
		else
		{
			tree_node_set_right (py, x);
		}
	}

	if (y != z)
	{
		tree_node_set_content (z, tree_node_get_content (y));
	}

	tree_node_free (y);
	(t->card)--; 

	return data;
}

void bin_tree_map_prefix (const BinTree *t, FILE *file, write_func_t f)
{
	assert (t != NULL);
	assert (f != NULL);
	assert (file != NULL);
	_bin_tree_map_prefix (tree_node_get_right (t->sent), NULL, file, f);
}

void bin_tree_map_infix (const BinTree *t, FILE *file, write_func_t f)
{
	assert (t != NULL);
	assert (f != NULL);
	assert (file != NULL);
	_bin_tree_map_infix (tree_node_get_right (t->sent), NULL, file, f);
}
	
void bin_tree_map_postfix (const BinTree *t, FILE *file, write_func_t f)
{
	assert (t != NULL);
	assert (f != NULL);
	assert (file != NULL);
	_bin_tree_map_postfix (tree_node_get_right (t->sent), NULL, file, f);
}


void bin_tree_dump (const BinTree *t, FILE *file, write_func_t f)
{
	assert (t != NULL);
	assert (file != NULL);
	fprintf (file, "<BIN_TREE REF=\"%p\" CARD=\"%d\" SENT=\"%p\">", (void *)t, t->card, (void *)(t->sent));

	_bin_tree_dump (tree_node_get_right (t->sent), NULL, file, f, BIN_TREE);

	fprintf (file, "</BIN_TREE>\n");
}

void bin_tree_foreach (BinTree *t, foreach_func_t f, void *data)
{
	assert (t != NULL);
	assert (f != NULL);
	_bin_tree_foreach (tree_node_get_right (t->sent), NULL, f, data);
}
