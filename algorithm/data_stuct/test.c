#include <stdio.h>
#include "list.h"
#include "base.h"

int main(void)
{
	int a[] = {1, 2, 3, 4, 5};

	List *l;

	l = list_new (int_cmp);

	int i;
	for (i = 0; i < ARRAY_LEN (a); i++)
	{
		list_insert_head (l, &a[i]);
	}

	list_dump (l, stdout, int_write);

	list_sort (l);

	list_dump (l, stdout, int_write);

	while (!list_is_empty (l))
	{
		list_delete_head (l);
	}

	list_dump (l, stdout, int_write);

	list_free (l);

	return 0;
}
