#include <stdlib.h>
#include <assert.h>
#include "list.h"
#include "listnode.h"

struct _list
{
	ListNode *sent;
	ListNode *end;
	int card;
	compare_func_t cmp_func;
};

List *list_new (compare_func_t f)
{
	List *l;

	assert (f != NULL);

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

	l->card = 0;

	l->cmp_func = f;

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

void list_set_compare_func (List *l, compare_func_t f)
{
	assert (l != NULL);
	l->cmp_func = f;
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

void *list_delete (List *l, void *data)
{
	ListNode *tmp;
	void *rt;

	assert (l != NULL);

	if (l->cmp_func == NULL)
	{
		fprintf (stderr, "List: compare func is NULL\n");
		return NULL;
	}
	
	for (tmp = list_node_get_next (l->sent); tmp != l->end; tmp = list_node_get_next (tmp))
	{
		if (l->cmp_func (list_node_get_content (tmp), data) == 0)
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

void *list_search (List *l, void *data)
{
	ListNode *tmp;

	assert (l != NULL);

	if (l->cmp_func == NULL)
	{
		fprintf (stderr, "List: compare func is NULL\n");
		return NULL;
	}

	for (tmp = list_node_get_next (l->sent); tmp != l->end; tmp = list_node_get_next (tmp))
	{
		if (l->cmp_func (list_node_get_content (tmp), data) == 0)
		{
			return list_node_get_content (tmp);
		}
	}

	return NULL;
}

void *list_search_by_position (List *l, int pos)
{
	ListNode *node;
	int i;

	assert (l != NULL);
	
	if (pos < 0 || pos >= (l->card))
	{
		return NULL;
	}

	node = list_node_get_next (l->sent);
	for (i = 0; i < pos; i++)
	{
		node = list_node_get_next (node);
	}

	return list_node_get_content (node);
}

void *list_search_max (List *l)
{
	ListNode *max;
	ListNode *tmp;

	assert (l != NULL);



	if (l->cmp_func == NULL)
	{
		fprintf (stderr, "List: compare func is NULL\n");
		return NULL;
	}

	if (l->card == 0)
	{
		fprintf (stderr, "List is emtpy\n");
		return NULL;
	}

	max = list_node_get_next (l->sent);
	for (tmp = list_node_get_next (max); tmp != l->end; tmp = list_node_get_next (tmp))
	{
		if (l->cmp_func (list_node_get_content (tmp), list_node_get_content (max)) > 0)
		{
			max = tmp;
		}
	}

	return list_node_get_content (max);
}

void *list_search_min (List *l)
{
	ListNode *min;
	ListNode *tmp;

	assert (l != NULL);

	if (l->cmp_func == NULL)
	{
		fprintf (stderr, "List: compare func is NULL\n");
		return NULL;
	}

	if (l->card == 0)
	{
		fprintf (stderr, "List is empty\n");
		return NULL;
	}

	min = list_node_get_next (l->sent);
	for (tmp = list_node_get_next (min); tmp != l->end; tmp = list_node_get_next (tmp))
	{
		if (l->cmp_func (list_node_get_content (tmp), list_node_get_content (min)) < 0)
		{
			min = tmp;
		}
	}

	return list_node_get_content (min);
}

void list_sort (List *l)
{
	assert (l != NULL);
	/*TODO */
}

void list_dump (List *l, FILE *file, write_func_t f)
{
	ListNode *node;
	assert (l != NULL);

	fprintf (file, "<LIST REF=\"%p\" CARD=\"%d\" SENT=\"%p\" END=\"%p\">", (void *)l, l->card, (void *)l->sent, (void *)l->end);
	for (node = list_node_get_next (l->sent); node != l->end; node = list_node_get_next (node))
	{
		list_node_dump (node, file, f);
	}
	fprintf (file, "</LIST>\n");
}

void list_foreach (List *l, foreach_func_t f, void *data)
{
	ListNode *node;
	assert (l != NULL);

	for (node = list_node_get_next (l->sent); node != l->end; node = list_node_get_next (node))
	{
		if (f (list_node_get_content (node), data) == false)
		{
			break;
		}
	}
}
