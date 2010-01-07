#include <assert.h>
#include <stdlib.h>
#include "treenode.h"
#include "_bintree.h"
#include "rbtree.h"

#define TREE_ROOT(T) (tree_node_get_right (T->sent))

static void left_rotate (RbTree *t, TreeNode *x);
static void right_rotate (RbTree *t, TreeNode *x);
static void rb_insert_fixup (RbTree *t, TreeNode *z);
static void rb_delete_fixup (RbTree *t, TreeNode *x);

struct _rbtree
{
	TreeNode *sent;
	int card;
	compare_func_t cmp_f;
};

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
	tree_node_set_right (t->sent, t->sent);
	tree_node_set_black (t->sent);

	t->card = 0;
	t->cmp_f = cmp_f;

	return t;
}

void rb_tree_free (RbTree *t)
{
	assert (t != NULL);
	rb_tree_flush (t);
	free (t->sent);
	free (t);
}

void rb_tree_flush (RbTree *t)
{
	assert (t != NULL);
	_bin_tree_flush (tree_node_get_right (t->sent), t->sent);
	tree_node_set_right (t->sent, t->sent);
	t->card = 0;
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

void rb_tree_insert (RbTree *t, void *data)
{
	TreeNode *x;
	TreeNode *y;
	TreeNode *z;
	
	assert (t != NULL);

	x = tree_node_get_right (t->sent);
	y = t->sent;

	z = tree_node_new_full (data, NULL, y, y);
	if (z == NULL)
	{
		return;
	}

	while (x != t->sent)
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

	tree_node_set_parent (z, y);

	if (y == t->sent)	/* root */
	{
		tree_node_set_right (t->sent, z);
	}
	else
	{
		if (t->cmp_f (data, tree_node_get_content (y)) < 0)
		{
			tree_node_set_left (y, z);
		}
		else
		{
			tree_node_set_right (y, z);
		}
	}

	tree_node_set_red (z);

	rb_insert_fixup (t, z);

	(t->card)++;
}

void *rb_tree_search (const RbTree *t, void *data)
{
	TreeNode *tmp;

	assert (t != NULL);

	tmp = _bin_tree_search (tree_node_get_right (t->sent), t->sent, t->cmp_f, data);
	
	return (tmp == NULL) ? NULL : tree_node_get_content (tmp);
}

void *rb_tree_delete (RbTree *t, void *data)
{
	TreeNode *x;	/* y's not SENTINEL child, or SENTINEL if y don't have child */
	TreeNode *y;	/* the node actually delete */
	TreeNode *z;	/* the node contain data */
	TreeNode *py;	/* parent of y */

	assert (t != NULL);

	z = _bin_tree_search (tree_node_get_right (t->sent), t->sent, t->cmp_f, data);
	if (z == NULL)
	{
		fprintf (stderr, "warning!, return an NULL\n");
		return NULL;
	}

	if ((tree_node_get_left (z) == t->sent) || (tree_node_get_right (z) == t->sent))
	{
		y = z;
	}
	else
	{
		y = _bin_tree_successor (z, t->sent);
	}

	if (tree_node_get_left (y) != t->sent)
	{
		x = tree_node_get_left (y);
	}
	else
	{
		x = tree_node_get_right (y);
	}

	py = tree_node_get_parent (y);
	tree_node_set_parent (x, py);

	if (py == t->sent)
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

	if (tree_node_is_black (y))
	{
		rb_delete_fixup (t, x);
	}

	tree_node_free (y);
	(t->card)--;

	return data;
}

void rb_tree_map_prefix (const RbTree *t, FILE *file, write_func_t f, void *data)
{
	assert (t != NULL);
	assert (file != NULL);
	assert (f != NULL);
	_bin_tree_map_prefix (tree_node_get_right (t->sent), t->sent, file, f, data);
}
	
void rb_tree_map_infix (const RbTree *t, FILE *file, write_func_t f, void *data)
{
	assert (t != NULL);
	assert (file != NULL);
	assert (f != NULL);
	_bin_tree_map_infix (tree_node_get_right (t->sent), t->sent, file, f, data);
}

void rb_tree_map_postfix (const RbTree *t, FILE *file, write_func_t f, void *data)
{
	assert (t != NULL);
	assert (file != NULL);
	assert (f != NULL);
	_bin_tree_map_postfix (tree_node_get_right (t->sent), t->sent, file, f, data);
}

void rb_tree_dump (const RbTree *t, FILE *file, write_func_t f, void *data)
{
	assert (t != NULL);
	assert (file != NULL);
	fprintf (file, "<RB_TREE REF=\"%p\" CARD=\"%d\" SENT=\"%p\">\n", (void *)t, t->card, (void *)(t->sent));

	_bin_tree_dump (tree_node_get_right (t->sent), t->sent, file, f, data, RB_TREE);

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
	y = tree_node_get_left (x);
	assert (y != NULL);

	/* Turn y's right subtree into x's left subtree */
	ry = tree_node_get_right (y);
	tree_node_set_left (x, ry);
	if (ry != t->sent)
	{
		tree_node_set_parent (ry, x);
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

static void rb_insert_fixup (RbTree *t, TreeNode *z)
{
	TreeNode *y;	/* z's uncle */
	TreeNode *pz;	/* z's parent */
	TreeNode *ppz;	/* z's parent's parent */

	static int i = 0;
	i++;

	while (tree_node_is_red (tree_node_get_parent (z))) /* so that p[p[z]] is black */
	{
		pz = tree_node_get_parent (z);
		ppz = tree_node_get_parent (pz);
		if (pz == tree_node_get_left (ppz))
		{
			y = tree_node_get_right (ppz);

			if (tree_node_is_red (y))
			{
				tree_node_set_black (pz);
				tree_node_set_black (y);
				tree_node_set_red (ppz);
				z = ppz;
			}
			else /* tree_node_is_black (y) */
			{
				if (z == tree_node_get_right (pz))
				{
					z = pz;
					left_rotate (t, z);
				}
				/* take care, z may has been changed */
				pz = tree_node_get_parent (z);
				ppz = tree_node_get_parent (pz);
	
				tree_node_set_black (pz);
				tree_node_set_red (ppz);
				right_rotate (t, ppz);
			}

		}
		else /* pz == tree_node_get_right (ppz) */
		{
			y = tree_node_get_left (ppz);

			if (tree_node_is_red (y))
			{
				tree_node_set_black (pz);
				tree_node_set_black (y);
				tree_node_set_red (ppz);
				z = ppz;
			}
			else /* tree_node_is_black (y) */
			{
				if (z == tree_node_get_left (pz))
				{
					z = pz;
					right_rotate (t, z);

					pz = tree_node_get_parent (z);
					ppz = tree_node_get_parent (pz);
				}
				
				tree_node_set_black (pz);
				tree_node_set_red (ppz);
				left_rotate (t, ppz);
			}
		}
	}

	tree_node_set_black (tree_node_get_right (t->sent));
}

static void rb_delete_fixup (RbTree *t, TreeNode *x)
{
	TreeNode *px;	/* x's parent */
	TreeNode *w;	/* x's brother */
	TreeNode *lw;
	TreeNode *rw;
	TreeNode *root;

	root = tree_node_get_right (t->sent);
	while ((x != root) && tree_node_is_black (x))
	{
		/* x is DOUBLE-BLACK now */
		px = tree_node_get_parent (x);
		if (x == tree_node_get_left (px))
		{
			w = tree_node_get_right (px);
			if (tree_node_is_red (w))
			{
				tree_node_set_black (w);
				tree_node_set_red (px);
				left_rotate (t, px);
				w = tree_node_get_right (px);
			}

			lw = tree_node_get_left (w);
			rw = tree_node_get_right (w);
			if (tree_node_is_black (lw) && tree_node_is_black (rw)) /* both child are black, so w can be red */
			{
				tree_node_set_red (w);
				x = px;
			}
			else /* one child or none are black, at least one is red */
			{
				if (tree_node_is_black (rw))	/* so that lw is red */
				{
					tree_node_set_black (lw);
					tree_node_set_red (w);
					right_rotate (t, w);
					w = tree_node_get_right (px);
					lw = tree_node_get_left (w);
					rw = tree_node_get_right (rw);
				}

				/* now rw is red */
				tree_node_is_red (px) ? tree_node_set_red (w) : tree_node_set_black (w);
				tree_node_set_black (px);
				tree_node_set_black (rw);
				left_rotate (t, px);
				x = root;
			}
		}
		else /* x == tree_node_get_right (px) */
		{
			w = tree_node_get_left (px);
			if (tree_node_is_red (w))
			{
				tree_node_set_black (w);
				tree_node_set_red (px);
				right_rotate (t, px);
				w = tree_node_get_left (px);
			}

			lw = tree_node_get_left (w);
			rw = tree_node_get_right (w);
			if (tree_node_is_black (lw) && tree_node_is_black (rw))
			{
				tree_node_set_red (w);
				x = px;
			}
			else /* one child or none are black, at least one is red */
			{
				if (tree_node_is_black (lw))
				{
					tree_node_set_black (rw);
					tree_node_set_red (w);
					left_rotate (t, w);
					w = tree_node_get_left (px);
					lw = tree_node_get_left (w);
					rw = tree_node_get_right (w);
				}

				/* now lw is red */
				tree_node_is_red (px) ? tree_node_set_red (w) : tree_node_set_black (w);
				tree_node_set_black (px);
				tree_node_set_black (lw);
				right_rotate (t, px);
				x = root;
			}
		}
	}
	tree_node_set_black (x);
}
