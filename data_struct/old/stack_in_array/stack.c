#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int IsEmpty (Stack S) {
	return (S->TopOfStack == EmptyTOS);
}

int IsFull (Stack S) {
	return (S->TopOfStack >= S->Capacity);
}

Stack CreateStack (int MaxElements) {
	Stack S;

	if (MaxElements < MinStackSize)
	{
		printf ("ERROR: Stack size is too small\n");
		exit (1);
	}

	S = malloc (sizeof (struct StackRecord));
	if (S == NULL)
	{
		fprintf (stderr, "Fatal Error: Out of space !\n");
		exit (1);
	}

	S->Array = malloc (sizeof(StackElementType) * MaxElements);
	if (S->Array == NULL)
	{
		fprintf (stderr, "Fatal Error: out of space !\n");
		exit (1);
	}

	S->Capacity = MaxElements;
	MakeEmpty (S);

	return S;
}

void DisposeStack (Stack S) {
	if (S != NULL)
	{
		free (S->Array);
		free (S);
	}
}

void MakeEmpty (Stack S) {
	S->TopOfStack = EmptyTOS;
}

void Push (StackElementType X, Stack S) {
	if ( IsFull (S))
	{
		printf ("ERROR: full stack\n");
		exit (1);
	} else
		S->Array[++S->TopOfStack] = X;
}


StackElementType Top (Stack S) {
	if (!IsEmpty (S))
		return S->Array[S->TopOfStack];
	fprintf (stderr, "Empty stack\n");
	return 0;
}

void Pop (Stack S) {
	if( IsEmpty (S))
		fprintf (stderr, "Empty stack\n");
	else
		S->TopOfStack--;
}

StackElementType TopAndPop (Stack S) {
	if (!IsEmpty (S))
		return S->Array[S->TopOfStack--];
	printf ("ERROR: Empty stack\n");
	return 0;
}
