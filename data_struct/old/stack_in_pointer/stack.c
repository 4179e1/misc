#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int IsEmpty (Stack S) {
	return (S->Next == NULL);
}

Stack CreateStack (void) {
	Stack S;

	S = malloc (sizeof (struct Node));
	if (S == NULL)
	{
		fprintf (stderr, "Fatal Error: Out of space !\n");
		exit (1);
	}
	S->Element = -1;
	S->Next = NULL;
	MakeEmpty (S);
	return S;
}

void DisposeStack (Stack S) {
	MakeEmpty (S);
//	free (S);
}

void MakeEmpty (Stack S) {
	if (S == NULL)
		fprintf(stderr, "Must use CreateStack first\n");
	else
		while (!IsEmpty(S))
			Pop (S);
}

void Push (StackElementType X, Stack S) {
	PtrToNode TmpCell;

	TmpCell = malloc (sizeof (struct Node));
	if (TmpCell == NULL)
	{
		fprintf (stderr, "Out of space!\n");
		exit (1);
	} else {
		/* stack has a header, the node behide the header 
		   is the top of the stack */
		TmpCell->Element = X;
		TmpCell->Next = S->Next;
		S->Next = TmpCell;
	}
}


StackElementType Top (Stack S) {
	if (!IsEmpty (S))
		return S->Next->Element;
	fprintf (stderr, "Empty stack\n");
	return 0;
}

void Pop (Stack S) {
	PtrToNode FirstCell;

	if( IsEmpty (S))
		fprintf (stderr, "Empty stack\n");
	else
	{
		FirstCell = S->Next;
		S->Next = S->Next->Next;
		free (FirstCell);
	}
}
