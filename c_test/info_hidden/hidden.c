#include <stdio.h>
#include <stdlib.h>
#include "hidden.h"

struct hidden
{
	int a;
	int b;
};

struct hidden *hidden_new (int a, int b)
{
	struct hidden *ptr;
	ptr = (struct hidden *)malloc (sizeof(struct hidden));
	if (ptr == NULL)
		fprintf (stderr, "malloc error\n");

	ptr->a = a;
	ptr->b = b;

	return ptr;
}

int geta (struct hidden *hide)
{
	return hide->a;
}

void seta (struct hidden *hide, int value)
{
	hide->a = value;
}

void hid_print (struct hidden *hide)
{
	printf ("a = %d, b = %d\n", hide->a, hide->b);
}
