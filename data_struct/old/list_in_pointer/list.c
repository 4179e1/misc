#include <stdio.h>
#include <stdlib.h>
#include "list.h"

List CreateList (void) {
	List L;

	L = malloc (sizeof(struct Node));

	L->Element = -1;
	L->Next = NULL;

	return L;
}

int IsEmpty (List L) {
	return (L->Next == NULL);
}

int IsLast (Position P, List L) {
	return (P->Next == NULL);
}

Position Find (ListElementType X, List L) {
	Position P;

	P = L->Next;

	while (P != NULL && P->Element != X)
		P = P->Next;

	return P;
}

void Delete (ListElementType X, List L) {

	Position P, TmpCell;

	P = FindPrevious (X, L);

	if (!IsLast (P, L))
	{
		TmpCell = P->Next;
		P->Next = TmpCell->Next;
		free (TmpCell);
	}
}

Position FindPrevious (ListElementType X, List L) {
	Position P;

	P = L;
	while (P->Next != NULL && P->Next->Element != X)
		P = P->Next;

	return P;
}

void Insert (ListElementType X, List L, Position P) {
	Position TmpCell;

	TmpCell = malloc (sizeof (struct Node));
	if (TmpCell == NULL)
		exit(1);

	TmpCell->Element = X;
	TmpCell->Next = P->Next;
	P->Next = TmpCell;
}

void DeleteList (List L) {
	Position P, Tmp;

	P = L->Next;
	L->Next = NULL;

	while (P != NULL)
	{
		Tmp = P->Next;
		free (P);
		P = Tmp;
	}
}

Position Header (List L) {
	return (Position) L;
}

Position First (List L) {
	return L->Next;
}

Position Advance (Position P) {
	return (P->Next);
}

ListElementType Retrieve (Position P) {
	return P->Element;
}
