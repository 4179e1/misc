#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void InitializeCursorSpace (void) {
	int i;

	for (i = 0; i < SPACESIZE; i++) {
		CursorSpace[i].Element = -1;
		CursorSpace[i].Next = i + 1;
	}

	CursorSpace[SPACESIZE - 1].Next = 0;
}

static Position CursorAlloc (void) {
	Position P;

	P = CursorSpace[0].Next;
	CursorSpace[0].Next = CursorSpace[P].Next;

	return P;
}

static void CursorFree (Position P) {
	CursorSpace[P].Next = CursorSpace[0].Next;
	CursorSpace[0].Next = P;
}

List CreateList (void) {
	List L;
	L = CursorAlloc();

	CursorSpace[L].Element = -1;
	CursorSpace[L].Next = 0;

	return L;
}

int IsEmpty (List L) {
	return (CursorSpace[L].Next == 0);
}

int IsLast (Position P, List L) {
	return (CursorSpace[P].Next == 0);
}

Position Find (ListElementType X, List L) {
	Position P;

	P = CursorSpace[L].Next;

	while (P && CursorSpace[P].Element != X)
		P = CursorSpace[P].Next;

	return P;
}

void Delete (ListElementType X, List L) {

	Position P, TmpCell;

	P = FindPrevious (X, L);

	if (!IsLast (P, L))
	{
		TmpCell = CursorSpace[P].Next;
		CursorSpace[P].Next = CursorSpace[TmpCell].Next;
		CursorFree (TmpCell);
	}
}

Position FindPrevious (ListElementType X, List L) {
	Position P, Tmp;

	P = L;
	while (CursorSpace[P].Next && CursorSpace[CursorSpace[P].Next].Element != X)
		P = CursorSpace[P].Next;

	return P;
}

void Insert (ListElementType X, List L, Position P) {
	Position TmpCell;

	TmpCell = CursorAlloc ();
	if (TmpCell == 0)
	{
		fprintf (stderr, "Out Of Space!\n");
		exit(1);
	}

	CursorSpace[TmpCell].Element = X;
	CursorSpace[TmpCell].Next = CursorSpace[P].Next;
	CursorSpace[P].Next = TmpCell;
}

void DeleteList (List L) {
	Position P, Tmp;

	P = CursorSpace[L].Next;
	CursorSpace[L].Next = 0;

	while (P)
	{
		Tmp = CursorSpace[P].Next;
		CursorFree (P);
		P = Tmp;
	}
}

Position Header (List L) {
	return (Position) L;
}

Position First (List L) {
	return CursorSpace[L].Next;
}

Position Advance (Position P) {
	return ( CursorSpace[P].Next);
}

ListElementType Retrieve (Position P) {
	return CursorSpace[P].Element;
}
