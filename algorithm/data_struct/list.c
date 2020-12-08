#include <stdlib.h>
#include <assert.h>
#include "list.h"
#include "listnode.h"

static ListNode *list_search_node (List *l, const void *data, compare_func_t cmp_f);
static ListNode *list_search_node_by_position (List *l, int pos);
static ListNode *list_merge_sort (List *l, ListNode *u, ListNode *z, compare_func_t cmp_f);
static ListNode *list_merge (List *l, ListNode *s, ListNode *t, ListNode *z, compare_func_t cmp_f);

struct _list
{
	ListNode *sent;
	ListNode *end;
	int card;
};

struct _list_cursor
{
	List *l;
	ListNode *n;
};

List *list_new (void)
{
	List *l;

	l = (List *)Malloc (sizeof (List));
	if (l == NULL)
	{
		return NULL;
	}
	
	l->sent = list_node_new ();
	if (l->sent == NULL)
	{
		free (l);
		return NULL;
	}

	l->end = list_node_new ();
	if (l->end == NULL)
	{
		free (l->sent);
		free (l);
		return NULL;
	}

	
	list_node_link (l->sent, l->end);
	list_node_set_prev (l->sent, l->sent);
	list_node_set_next (l->end, l->end);

	l->card = 0;

	return l;
}

void list_free (List *l)
{
	assert (l != NULL);
	list_flush (l);
	free (l->sent);
	free (l->end);
	free (l);
}

void list_flush (List *l)
{
	ListNode *tmp;
	ListNode *save;

	assert (l != NULL);

	tmp = list_node_get_next (l->sent); 
	while (tmp != l->end)
	{
		save = tmp;
 		tmp = list_node_get_next (tmp);
		list_node_free (save);
	}

	list_node_link (l->sent, l->end);
	l->card = 0;
}

bool list_is_empty (List *l)
{
	assert (l != NULL);
	return (l->card == 0);
}

int list_get_card (List *l)
{
	assert (l != NULL);
	return l->card;
}

void list_insert_head (List *l, void *data)
{
	ListNode *node;

	assert (l != NULL);

	node = list_node_new ();
	if (node == NULL)
	{
		return;
	}
	list_node_set_content (node, data);

	list_node_link (node, list_node_get_next (l->sent));
	list_node_link (l->sent, node);

	(l->card)++;
}

void list_insert_tail (List *l, void *data)
{
	ListNode *node;

	assert (l != NULL);

	node = list_node_new ();
	if (node == NULL)
	{
		return;
	}
	list_node_set_content (node, data);

	list_node_link (list_node_get_prev (l->end), node);
	list_node_link (node, l->end);

	(l->card)++;
}

void *list_head (List *l)
{
	assert (l != NULL);
	return list_node_get_content (list_node_get_next (l->sent));
}

void *list_tail (List *l)
{
	assert (l != NULL);
	return list_node_get_content (list_node_get_prev (l->end));
}

void *list_delete_head (List *l)
{
	ListNode *head;
	ListNode *tmp;
	void *data;

	assert (l != NULL);

	head = list_node_get_next (l->sent);
	tmp = list_node_get_next (head);

	list_node_link (l->sent, tmp);
	(l->card)--;

	data = list_node_get_content (head);
	list_node_free (head);
	return data;
}

void *list_delete_tail (List *l)
{
	ListNode *tail;
	ListNode *tmp;
	void *data;

	assert (l != NULL);

	tail = list_node_get_prev (l->end);
	tmp = list_node_get_prev (tail);

	list_node_link (tail, tmp);
	(l->card)--;

	data = list_node_get_content (tail);
	list_node_free (tail);
	return tail;
}

void *list_delete (List *l, const void *data, compare_func_t cmp_f)
{
	ListNode *tmp;
	void *rt;

	assert (l != NULL);
	assert (cmp_f != NULL);
	
	for (tmp = list_node_get_next (l->sent); tmp != l->end; tmp = list_node_get_next (tmp))
	{
		if (cmp_f (list_node_get_content (tmp), data) == 0)
		{
			/* found */
			list_node_link (list_node_get_prev (tmp), list_node_get_next (tmp));
			(l->card)--;

			rt = list_node_get_content (tmp);
			list_node_free (tmp);
			return rt;
		}
	}

	return NULL;
}

void *list_search (List *l, const void *data, compare_func_t cmp_f)
{
	ListNode *tmp;

	assert (l != NULL);
	assert (cmp_f != NULL);

	tmp = list_search_node (l, data, cmp_f);
	if (tmp == NULL)
	{
		return NULL;
	}

	return list_node_get_content (tmp);
}


void *list_search_by_position (List *l, int pos)
{
	ListNode *node;

	assert (l != NULL);

	node = list_search_node_by_position (l, pos);
	if (node == NULL)
	{
		return NULL;
	}

	return list_node_get_content (node);
}

void *list_search_max (List *l, compare_func_t cmp_f)
{
	ListNode *max;
	ListNode *tmp;

	assert (l != NULL);
	assert (cmp_f != NULL);

	max = list_node_get_next (l->sent);
	for (tmp = list_node_get_next (max); tmp != l->end; tmp = list_node_get_next (tmp))
	{
		if (cmp_f (list_node_get_content (tmp), list_node_get_content (max)) > 0)
		{
			max = tmp;
		}
	}

	if (max == l->end)
	{
		return NULL;
	}

	return list_node_get_content (max);
}

void *list_search_min (List *l, compare_func_t cmp_f)
{
	ListNode *min;
	ListNode *tmp;

	assert (l != NULL);
	assert (cmp_f != NULL);

	if (l->card == 0)
	{
		fprintf (stderr, "List is empty\n");
		return NULL;
	}

	min = list_node_get_next (l->sent);
	for (tmp = list_node_get_next (min); tmp != l->end; tmp = list_node_get_next (tmp))
	{
		if (cmp_f (list_node_get_content (tmp), list_node_get_content (min)) < 0)
		{
			min = tmp;
		}
	}

	if (min == l->end)
	{
		return NULL;
	}

	return list_node_get_content (min);
}

void list_sort (List *l, compare_func_t cmp_f)
{
	assert (l != NULL);
	assert (cmp_f != NULL);

	list_node_link (l->sent, list_merge_sort (l, list_node_get_next (l->sent), l->end, cmp_f));
}

void list_dump (List *l, FILE *file, write_func_t f, void *data)
{
	ListNode *node;
	assert (l != NULL);
	assert (file != NULL);

	fprintf (file, "<LIST REF=\"%p\" CARD=\"%d\" SENT=\"%p\" END=\"%p\">", (void *)l, l->card, (void *)l->sent, (void *)l->end);
	for (node = list_node_get_next (l->sent); node != l->end; node = list_node_get_next (node))
	{
		list_node_dump (node, file, f, data);
	}
	fprintf (file, "</LIST>\n");
}

void list_foreach (List *l, foreach_func_t f, void *data)
{
	ListNode *node;
	assert (l != NULL);
	assert (f != NULL);

	for (node = list_node_get_next (l->sent); node != l->end; node = list_node_get_next (node))
	{
		if (f (list_node_get_content (node), data) == false)
		{
			break;
		}
	}
}

/* List Cursor */
ListCursor *list_cursor_new (List *l)
{
	ListCursor *lc;

	assert (l != NULL);

	lc = (ListCursor *)Malloc (sizeof (ListCursor));
	if (lc == NULL)
	{
		return NULL;
	}

	lc->l = l;
	lc->n = list_node_get_next (l->sent);

	return lc;
}

void list_cursor_free (ListCursor *lc)
{
	assert (lc != NULL);

	free (lc);
}

bool list_cursor_is_head (const ListCursor *lc)
{
	assert (lc != NULL);

	if (list_is_empty (lc->l))
	{
		return false;
	}

	return (lc->n == list_node_get_next (lc->l->sent));
}

bool list_cursor_is_tail (const ListCursor *lc)
{
	assert (lc != NULL);
	if (list_is_empty (lc->l))
	{
		return false;
	}

	return (lc->n == list_node_get_prev (lc->l->end));
}
			
void list_cursor_move_to_head (ListCursor *lc)
{
	assert (lc != NULL);

	lc->n = list_node_get_next (lc->l->sent);
}

void list_cursor_move_to_tail (ListCursor *lc)
{
	assert (lc != NULL);

	lc->n = list_node_get_prev (lc->l->end);
}

void list_cursor_step_forward (ListCursor *lc)
{
	assert (lc != NULL);

	lc->n = list_node_get_next (lc->n);
}

void list_cursor_step_backward (ListCursor *lc)
{
	assert (lc != NULL);

	lc->n = list_node_get_prev (lc->n);
}

void *list_cursor_move_to_value (ListCursor *lc, void *value, compare_func_t cmp_f)
{
	ListNode *n;

	assert (lc != NULL);

	n = list_search_node (lc->l, value, cmp_f);

	if (n == NULL)
	{
		return NULL;
	}

	lc->n = n;
	return list_node_get_content (n);
}

void *list_cursor_move_to_position (ListCursor *lc, int pos)
{
	ListNode *n;

	assert (lc != NULL);

	n = list_search_node_by_position (lc->l, pos);

	if (n == NULL)
	{
		return NULL;
	}

	lc->n = n;
	return list_node_get_content (n);
}

void list_cursor_set_content (ListCursor *lc, void *data)
{
	assert (lc != NULL);

	if ((lc->n == lc->l->sent) || (lc->n == lc->l->end))
	{
		return;
	}

	list_node_set_content (lc->n ,data);
}

void *list_cursor_get_content (ListCursor *lc)
{
	assert (lc != NULL);

	if ((lc->n == lc->l->sent) || (lc->n == lc->l->end))
	{
		return NULL;
	}

	return list_node_get_content (lc->n);
}

void list_cursor_insert_before (ListCursor *lc, void *data)
{
	ListNode *tmp;

	assert (lc != NULL);

	if ((lc->n == lc->l->sent) || (lc->n == lc->l->end))
	{
		return;
	}

	tmp = list_node_new_full (data, NULL, NULL);
	if (tmp == NULL)
	{
		return;
	}

	list_node_insert_before (lc->n, tmp);
	(lc->l->card)++;
}
	
void list_cursor_insert_after (ListCursor *lc, void *data)
{
	ListNode *tmp;

	assert (lc != NULL);

	if ((lc->n == lc->l->sent) || (lc->n == lc->l->end))
	{
		return;
	}

	tmp = list_node_new_full (data, NULL, NULL);
	if (tmp == NULL)
	{
		return;
	}

	list_node_insert_after (lc->n, tmp);
	(lc->l->card)++;
}

void *list_cursor_remove (ListCursor *lc)
{
	ListNode *p;
	ListNode *n;
	void *data;

	assert (lc != NULL);

	if ((lc->n == lc->l->sent) || (lc->n == lc->l->end))
	{
		return NULL;
	}

	n = list_node_get_next (lc->n);
	if (n == lc->l->end)
	{
		return NULL;
	}
	p = list_node_get_prev (lc->n);

	data = list_node_get_content (lc->n);
	list_node_free (lc->n);
	list_node_link (p, n);
	(lc->l->card)--;
	
	lc->n = n;

	return data;
}

void *list_cursor_remove_before (ListCursor *lc)
{
	ListNode *tmp;
	ListNode *p;
	void *data;

	assert (lc != NULL);

	if ((lc->n == lc->l->sent) || (lc->n == lc->l->end))
	{
		return NULL;
	}

	tmp = list_node_get_prev (lc->n);
	if (tmp == lc->l->sent)
	{
		return NULL;
	}

	p = list_node_get_prev (tmp);
	data = list_node_get_content (tmp);
	list_node_free (tmp);
	list_node_link (p, lc->n);
	(lc->l->card)--;

	return data;
}
	
void *list_cursor_remove_after (ListCursor *lc)
{
	ListNode *tmp;
	ListNode *n;
	void *data;
	
	assert (lc != NULL);

	if ((lc->n == lc->l->sent) || (lc->n == lc->l->end))
	{
		return NULL;
	}

	tmp = list_node_get_next (lc->n);
	if (tmp == lc->l->end)
	{
		return NULL;
	}

	n = list_node_get_next (tmp);
	data = list_node_get_content (tmp);
	list_node_free (tmp);
	list_node_link (lc->n, n);
	(lc->l->card)--;

	return data;
}

/* private func */
static ListNode *list_search_node (List *l, const void *data, compare_func_t cmp_f)
{
	ListNode *tmp;

	for (tmp = list_node_get_next (l->sent); tmp != l->end; tmp = list_node_get_next (tmp))
	{
		if (cmp_f (list_node_get_content (tmp), data) == 0)
		{
			return tmp;
		}
	}

	return NULL;
}

static ListNode *list_search_node_by_position (List *l, int pos)
{
	ListNode *node;	
	int i;

	if (pos < 0 || pos >= (l->card))
	{
		return NULL;
	}

	node = list_node_get_next (l->sent);
	for (i = 0; i < pos; i++)
	{
		node = list_node_get_next (node);
	}

	return node;
}

static ListNode *list_merge_sort (List *l, ListNode *u, ListNode *z, compare_func_t cmp_f)
{
	ListNode *s;
	ListNode *t;

	if (list_node_get_next (u) == z)
	{
		return u;
	}

	s = u;
	t = list_node_get_next (list_node_get_next (list_node_get_next (u)));
	/* t run twice faster than u, when t meet z, u is at the middle of the list */
	while (t != z)
	{
		u = list_node_get_next (u);
		t = list_node_get_next (list_node_get_next (t));
	}

	/* so we link two sub-list to z */
	t = list_node_get_next (u);
	list_node_set_next (u, z);

	return list_merge (l, list_merge_sort (l, s, z, cmp_f), list_merge_sort (l, t, z, cmp_f), l->end, cmp_f);
}

static ListNode *list_merge (List *l, ListNode *s, ListNode *t, ListNode *z, compare_func_t cmp_f)
{
	/* 
	 * the node u is the last element of the new list begin from z
	 * s------->
	 *          z------>u
	 * t------->
	 */
	ListNode *u = z;

	do {
		if (t == z)
		{
			list_node_link (u, s);
			u = s;
			s = list_node_get_next (s);
			continue;
		}

		if (s == z)
		{
			list_node_link (u, t);
			u = t;
			t = list_node_get_next (t);
			continue;
		}

		if (cmp_f (list_node_get_content (s), list_node_get_content (t)) <= 0)
		{
			list_node_link (u, s);
			u = s;
			s = list_node_get_next (s);
		}
		else
		{
			list_node_link (u, t);
			u = t;
			t = list_node_get_next (t);
		}
	} while (u != z);

	/* now u is the begining of list, and we fix the broken sentinal z */
	u = list_node_get_next (z);
	list_node_set_next (z, z);

	return u;
}
