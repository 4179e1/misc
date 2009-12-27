#include <stdio.h>
#include "base.h"
#include "hash.h"

int int_key (void *data)
{
	return sum_key(data, sizeof(int));
}

int main(void)
{
	int a[] = {1, 2, 3, 4, 5, 12, 14, 16, 18, 20, 123456};

	Hash *h;

	h = hash_new (10, int_key, int_cmp);

	int i;
	for (i = 0; i < ARRAY_LEN (a); i++)
	{
		hash_insert (h, &a[i]);
	}
	
	hash_dump (h, stdout, int_write);

	for (i = 0; i < ARRAY_LEN (a); i++)
	{
		printf ("%d\n", *(int *)hash_delete (h, &a[i]));
	}

	hash_dump (h, stdout, int_write);

	hash_free (h);

	return 0;
}
