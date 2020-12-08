#include <stdio.h>
#include "stack.h"

int main (void) {
	Stack stack;
	stack = CreateStack(100);

	int i;
	for (i = 0; i < 5; i++) {
		Push (i, stack);
	}

	while (!IsEmpty (stack)) {
		printf ("%d\n", Top (stack));
		Pop (stack);
	}

	return 0;
}
