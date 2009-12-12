#include "stack.h"
#include "ListNode.h"

int main(void)
{
	ListNode *n1 = list_node_new ();
	ListNode *n2 = list_node_new ();
	list_node_link (n1, n2);
	list_node_dump (n1, stdout, NULL);
	list_node_dump (n2, stdout, NULL);
	list_node_unlink (n1, n2);
	list_node_dump (n1, stdout, NULL);

	list_node_free (n1);
	list_node_free (n2);

	return 0;
}
