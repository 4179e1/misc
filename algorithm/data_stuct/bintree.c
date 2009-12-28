#include "bintree.h"
#include "treenode.h"

static int tree_height (TreeNode *n);
static void *tree_search (TreeNode *n, comapre_func_t f, void *data);

static TreeNode *minimum_node (TreeNode *n);
static TreeNode *maximum_node (TreeNode *n);

static void map_prefix (TreeNode *n, write_func_t f, FILE *file);
static void map_infix (TreeNode *n, write_func_t f, FILE *file);
static void map_posfix (TreeNode *n, write_func_t f, FILE *file);

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
}

int bin_tree_get_card (const BinTree *t)
{
	assert (t != NULL);
	return t->card;
}

int bin_tree_get_height (const BinTree *t)
{
	assert (t != NULL);
	if (t->card != 0)
	{
		return tree_height (tree_node_get_right (t->sent));
	}
	return 0;
}

void *bin_tree_get_root (const BinTree *t)
{
	assert (t != NULL);

	if (t->card != 0)
	{
		return tree_node_get_content (tree_node_get_right (t->sent));
	}

	return NULL;
}

void *bin_tree_get_minimum (const Bintree *t)
{
	assert (t != NULL);
	if (t->card != 0)
	{
		return tree_node_get_content (minimum_node (tree_node_get_right (t->sent)));
	}

	return NULL;
}

void *bin_tree_get_maximum (const Bintree *t)
{
	assert (t != NULL);
	if (t->card != 0)
	{
		return tree_node_get_content (maximum_node (tree_node_get_right (t->sent)));
	}

	return NULL;
}

void bin_tree_insert (BinTree *t, void *data);
void *bin_tree_search (const BinTree *t, void *data)
{
	assert (t != NULL);

	if (t->card != 0)
	{
		return tree_search (tree_node_get_right (t->sent), t->cmp_f, void *data);
	}

	return NULL;
}
void *bin_tree_delete (BinTree *t, void *data);

void bin_tree_map_prefix (const BinTree *t, write_func_t f, FILE *file)
{
	assert (t != NULL);
	assert (f != NULL);
	assert (file != NULL);
	map_prefix (tree_node_get_right (t->sent), f, file);
}

void bin_tree_map_infix (const BinTree *t, write_func_t f, FILE *file)
{
	assert (t != NULL);
	assert (f != NULL);
	assert (file != NULL);
	map_infix (tree_node_get_right (t->sent), f, file);
}
	
void bin_tree_map_postfix (const BinTree *t, write_func_t f, FILE *file)
{
	assert (t != NULL);
	assert (f != NULL);
	assert (file != NULL);
	map_postfix (tree_node_get_right (t->sent), f, file);
}


void bin_tree_dump (const BinTree *t, FILE *file, write_func_t f);
void bin_tree_foreach (BinTree *t, foreach_func_t f, void *data);


/* private func */

static int tree_height (TreeNode *n)
{
	int l, r;

	if (tree_node_is_leaf (n))
	{
		return 0;
	}

	l = tree_height (n->left);
	r = tree_height (n->right);

	return (MAX (l, r) + 1);
}

static void *tree_search (TreeNode *n, comapre_func_t f, void *data)
{
	int i;
	while ((n != NULL) && ((i = f (data, tree_node_get_content (f))) != 0))
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
static TreeNode *minimum_node (TreeNode *n)
{
	TreeNode *tmp;
	while ((tmp = tree_node_get_left (n)) != NULL)
	{
		n = tmp;
	}
	return n;
}

static TreeNode *maximum_node (TreeNode *n)
{
	TreeNode *tmp;
	while ((tmp = tree_node_get_right (n)) != NULL)
	{
		n = tmp;
	}
	return n;
}

static void map_prefix (TreeNode *n, write_func_t f, FILE *file)
{
	if (n != NULL)
	{
		f (tree_node_get_content (n), file);
		map_prefix (tree_node_get_left (n), f, file);
		map_prefix (tree_node_get_right (n), f, file);
	}
}

static void map_infix (TreeNode *n, write_func_t f, FILE *file)
{
	if (n != NULL)
	{
		map_infix (tree_node_get_left (n), f, file);
		f (tree_node_get_content (n), file);
		map_infix (tree_node_get_right (n), f, file);
	}
}

static void map_posfix (TreeNode *n, write_func_t f, FILE *file)
{
	if (n != NULL)
	{
		map_postfix (tree_node_get_left (n), f, file);
		map_postfix (tree_node_get_right (n), f, file);
		f (tree_node_get_content (n), file);
	}
}
