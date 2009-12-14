#include "list.h"
#include "base.h"

int main(void)
{
	List *l;

	l = list_new (int_cmp);

	int a[] = {1, 2, 3, 4, 5};

	int i;
	for (i = 0; i < ARRAY_LEN (a); i++)
	{
		list_insert_tail (l, &a[i]);
	}
	list_sort (l);

	list_dump (l, stdout, int_write);

	while (!list_is_empty(l))
	{
		printf ("%d\t", *(int *)list_delete_tail(l));
	}

	list_dump (l, stdout, NULL);

	list_free (l);

	return 0;
}
