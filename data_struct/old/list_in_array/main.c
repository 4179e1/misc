#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(void) {
	List list;
	InitializeCursorSpace();
	list = CreateList ();

	Position P = (Position) list;
	
	int i;
	for ( i = 0; i < 8; i++)
	{
		Insert (i, list, P);
		P = Advance (P);
	}

	if (P = Find (5, list))
	{
		printf ("pos: %d\n", Retrieve(P));
		Delete (5, list);
	}

	P = (Position) list;
	while (!IsLast(P, list))
	{
		printf ("%d\n", Retrieve(P));
		P = Advance (P);
	}
	printf ("%d\n", Retrieve(P));

	printf ("%d\n", Retrieve(Header(list)));
	printf ("%d\n", Retrieve(First(list)));

	DeleteList (list);
	if (IsEmpty)
		printf ("Empty list\n");

	return 0;
}
