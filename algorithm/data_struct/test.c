#include <stdio.h>
#include "base.h"
#include "rbtree.h"


int main(void)
{
	int a[] = {5, 2, 1, 3, 4, 9, 8, 7};
	int b = 6;

	RbTree *t;

	t = rb_tree_new (int_cmp);
	rb_tree_dump (t, stdout, int_write);

	int i;
	for (i = 0; i < ARRAY_LEN (a); i++)
	{
		rb_tree_insert (t, &a[i]);
	}

	rb_tree_dump (t, stdout, int_write);

	for (i = 0; i < ARRAY_LEN (a); i++)
	{
		printf ("%d\t", *(int *)rb_tree_delete (t, &a[i]));
	}

	printf ("after delete\n");
	rb_tree_dump (t, stdout, int_write);

	rb_tree_free (t);

	return 0;
}
