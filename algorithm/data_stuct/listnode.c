#include <stdlib.h>
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
	return (ListNode *)Malloc (sizeof (ListNode));
}

void list_node_free (ListNode *n)
{
	free (n);
}
