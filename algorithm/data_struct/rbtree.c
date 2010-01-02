#include <assert.h>
#include "treenode.h"
#include "_bintree.h"

static void left_rotate (RbTree *t, TreeNode *x);
static void right_rotate (RbTree *t, TreeNode *x);

struct _rbtree
{
	TreeNode *sent;
	int card;
	compare_func_t cmp_f;
}

RbTree *rb_tree_new (compare_func_t cmp_f)
{
	RbTree *t;

	assert (cmp_f != NULL);
	
	t = (RbTree *) Malloc (sizeof (RbTree));
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
	tree_node_set_black (t->sent);

	t->card = 0;
	t->cmp_f = cmp_f;

	return t;
}

void rb_tree_free (RbTree *t)
{
	assert (t != NULL);
	rb_tree_flush (t);
	free (rb->sent);
	free (rb);
}

void rb_tree_flush (RbTree *t)
{
	assert (t != NULL);
	_bin_tree_flush (tree_node_get_right (t->sent), t->sent);
}

bool rb_tree_is_empty (const RbTree *t)
{
	assert (t != NULL);
	return (t->card == 0);
}

int rb_tree_get_card (const RbTree *t)
{
	assert (t != NULL);
	return (t->card);
}

int rb_tree_get_height (const RbTree *t)
{
	assert (t != NULL);
	return _bin_tree_height (tree_node_get_right (t->sent), t->sent);
}

void *rb_tree_get_root (const RbTree *t)
{
	assert (t != NULL);
	return tree_node_get_content (tree_node_get_right (t->sent));
}

void *rb_tree_get_minimum (const RbTree *t)
{
	assert (t != NULL);
	return _bin_tree_minimum (tree_node_get_right (t->sent), t->sent);
}

void *rb_tree_get_maximum (const RbTree *t)
{
	assert (t != NULL);
	return _bin_tree_maximum (tree_node_get_right (t->sent), t->sent);
}

void rb_tree_insert (RbTree *t, void *data);
void *rb_tree_search (const RbTree *t, void *data);
void *rb_tree_delete (rbtree *t, void *data);

void rb_tree_map_prefix (const RbTree *t, FILE *file, write_func_t f)
{
	assert (t != NULL);
	assert (file != NULL);
	assert (f != NULL);
	_bin_tree_map_prefix (tree_node_get_right (t->sent), t->sent, file, f);
}
	
void rb_tree_map_infix (const RbTree *t, FILE *file, write_func_t f)
{
	assert (t != NULL);
	assert (file != NULL);
	assert (f != NULL);
	_bin_tree_map_infix (tree_node_get_right (t->sent), t->sent, file, f);
}

void rb_tree_map_postfix (cosnt RbTree *t, FILE *file, write_func_t f)
{
	assert (t != NULL);
	assert (file != NULL);
	assert (f != NULL);
	_bin_tree_map_postfix (tree_node_get_right (t->sent), t->sent, file, f);
}

void rb_tree_dump (cosnt RbTree *t, FILE *file, write_func_t f)
{
	assert (t != NULL);
	assert (file != NULL);
	fprintf (file, "<RB_TREE REF=\"%p\" CARD=\"%d\" SENT=\"%p\">", (void *)t, t->card, (void *)(t->sent));

	_bin_tree_dump (tree_node_get_right (t->sent), NULL, file, f, RB_TREE);

	fprintf (file, "</RB_TREE>\n");	
}

void rb_tree_foreach (RbTree *t, foreach_func_t f, void *data)
{
	assert (t != NULL);
	assert (f != NULL);
	_bin_tree_foreach (tree_node_get_right (t->sent), t->sent, f, data);
}

/* private func */
static void left_rotate (RbTree *t, TreeNode *x)
{
	TreeNode *y;
	TreeNode *ly;
	TreeNode *px;

	assert (t != NULL);
	assert (x != NULL);

	/* Set y */
	y = tree_node_get_right (x);
	assert (y != NULL);

	/* Turn y's left subtree into x's right subtree */
	ly = tree_node_get_left (y);
	tree_node_set_right (x, ly);
	if (ly != t->sent)
	{
		tree_node_set_parent (ly, x);
	}
	
	/* Link x's parent to y */
	px = tree_node_get_parent (x);
	tree_node_set_parent (y, px);
	if (px == t->sent)	/* root */
	{
		tree_node_set_right (t->sent, y);
	}
	else
	{
		if (x == tree_node_get_left (px))
		{
			tree_node_set_left (px, y);
		}
		else /* x == tree_node_get_right (px) */
		{
			tree_node_set_right (px, y);
		}
	}

	/* Put x on y's left*/
	tree_node_set_left (y, x);
	tree_node_set_parent (x, y);
}

static void right_rotate (RbTree *t, TreeNode *x)
{
	TreeNode *y;
	TreeNode *ry;
	TreeNode *px;

	assert (t != NULL);
	assert (x != NULL);

	/* Set y */
	y = tree_node_get_left (y);
	assert (y != NULL);

	/* Turn y's right subtree into x's left subtree */
	ry = tree_node_get_riht (y);
	tree_node_set_left (x, ry);
	if (ry != t->sent)
	{
		tree_node_get_parent (ry, x);
	}

	/* Link x's parent to y */
	px = tree_node_get_parent (x);
	tree_node_set_parent (y, px);
	if (px == t->sent)
	{
		tree_node_set_right (t->sent, y);
	}
	else
	{
		if (x == tree_node_get_left (px))
		{
			tree_node_set_left (px, y);
		}
		else /* x == tree_node_get_right (px) */
		{
			tree_node_set_right (px, y);
		}
	}
	
	/* Put x on y's right */
	tree_node_set_right (y, x);
	tree_node_set_parent (x, y);
}
