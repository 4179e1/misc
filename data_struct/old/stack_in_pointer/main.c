#include <stdio.h>
#include "stack.h"

int main (void) {
	Stack stack;
	stack = CreateStack();

	int i;
	for (i = 0; i < 5; i++) {
		Push (i, stack);
	}

	while (!IsEmpty (stack)) {
		printf ("%d\n", Top (stack));
		Pop (stack);
	}
	
	DisposeStack (stack);
	printf ("%d\n", stack->Element);
	free (stack);
	stack = NULL;

	if (stack == NULL)
	{
		printf ("stack has been disposed\n");
	}
	return 0;
}
