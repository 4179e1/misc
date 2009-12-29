#include <stdio.h>
#include "base.h"
#include "bintree.h"


int main(void)
{
	int a[] = {5, 2, 1, 3, 4, 9, 8, 7};
	int b = 123;

	BinTree *t;

	t = bin_tree_new (int_cmp);

	int i;

	for (i = 0; i < ARRAY_LEN (a); i++)
	{
		bin_tree_insert (t, &a[i]);
	}
	
	bin_tree_dump (t, stdout, int_write);

	for (i = 0; i < ARRAY_LEN (a); i++)
	{
		printf ("%d\t", *(int *)bin_tree_delete (t, &a[i]));
	}

	bin_tree_dump (t, stdout, int_write);

	bin_tree_free (t);

	return 0;
}
