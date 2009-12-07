#include "stack.h"

int main(void)
{
	Stack *s;
	s = stack_new (1);
	
	int array[] = {1, 2, 3, 4, 5};
	int i;
	for (i = 0; i < ARRAY_LEN (array); i++)
	{
		stack_push (s, &(array[i]));
	}

	stack_dump (s, stdout);

	while (!stack_is_empty (s))
	{
		printf ("%d", *(int *)(stack_pop (s)));
	}

	stack_free (s);
	return 0;
}
