#include <stdlib.h>
#include <assert.h>
#include "listnode.h"
#include "base.h"

struct _list_node
{
	void *data;
	struct _list_node *prev;
	struct _list_node *next;
};

ListNode *list_node_new (void)
{
	ListNode *node;
	node = (ListNode *)Malloc (sizeof (ListNode));
	if (node == NULL)
	{
		return NULL;
	}
	node->data = NULL;
	node->prev = NULL;
	node->next = NULL;
	return node;
}

ListNode *list_node_new_full (void *data, ListNode *p, ListNode *n)
{
	ListNode *node;
	node = (ListNode *)Malloc (sizeof (ListNode));
	if (node == NULL)
	{
		return NULL;
	}
	node->data = data;
	node->prev = p;
	node->next = n;
	return node;
}

void list_node_free (ListNode *n)
{
	free (n);
}

void list_node_set_content (ListNode *node, void *data)
{
	assert (node != NULL);
	node->data = data;
}

void list_node_set_next (ListNode *node, ListNode *next)
{
	assert (node != NULL);
	node->next = next;
}

void list_node_set_prev (ListNode *node, ListNode *prev)
{
	assert (node != NULL);
	node->prev = prev;
}

void *list_node_get_content (const ListNode *node)
{
	assert (node != NULL);
	return node->data;
}

ListNode *list_node_get_next (const ListNode *node)
{
	assert (node != NULL);
	return node->next;
}

ListNode *list_node_get_prev (const ListNode *node)
{
	assert (node != NULL);
	return node->prev;
}

void list_node_link (ListNode *prev, ListNode *next)
{
	assert (prev != NULL);
	assert (next != NULL);
	prev->next = next;
	next->prev = prev;
}

void list_node_unlink (ListNode *prev, ListNode *next)
{
	assert (prev != NULL);
	assert (prev != NULL);
	prev->next = NULL;
	next->prev = NULL;
}

void list_node_insert_before (ListNode *n, ListNode *prev)
{
	ListNode *tmp;

	assert (n != NULL);
	assert (prev != NULL);

	tmp = n->prev;
	list_node_link (prev, n);

	prev->prev = tmp;
	if (tmp)
	{
		tmp->next = prev;
	}
}

void list_node_insert_after (ListNode *n, ListNode *next)
{
	ListNode *tmp;
	
	assert (n != NULL);
	assert (next != NULL);

	tmp = n->next;
	list_node_link (n, next);

	next->next = tmp;
	if (tmp)
	{
		tmp->prev = next;
	}
}

void list_node_dump (const ListNode *node, FILE *file, write_func_t f)
{
	assert (node != NULL);
	assert (file != NULL);

	fprintf (file, "<LIST_NODE REF=\"%p\" CONTENT=\"%p\" PREV=\"%p\" NEXT=\"%p\">", (void *)node, (void *)node->data, (void *)node->prev, (void *)node->next);
	if (f)
	{
		f(node->data, file);
	}
	fprintf (file, "</LIST_NODE>\n");
}
