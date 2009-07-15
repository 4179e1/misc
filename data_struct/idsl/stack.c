#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "idsl_stack.h"

#define COUNT 10

struct _stack_element_type {
	int a;
	int b;
};

idsl_element_t stack_alloc (void *user_data) {
	struct _stack_element_type *astack_element;
	astack_element = (struct _stack_element_type *)malloc (sizeof(struct _stack_element_type));
	if (astack_element == NULL)
	{
		fprintf (stderr, "ERROR: not enough space\n");
		return NULL;
	}

	if (user_data != NULL) {
		memcpy (astack_element, user_data, sizeof(struct _stack_element_type));
	}

	return (idsl_element_t)astack_element;
}

void stack_free (idsl_element_t E) {
	if (E != NULL)
		free(E);
	return;
}

int main(void) {
	idsl_stack_t s;
	struct _stack_element_type temp;
	struct _stack_element_type *another_temp;


	s = idsl_stack_alloc ("a stack", stack_alloc, stack_free);
	if (s == NULL) {
		fprintf (stderr, "create stack failed\n");
		exit(1);
	}

	int i;
	for (i = 0; i < COUNT; i++){
		temp.a = i;
		temp.b = i;

		idsl_stack_push (s, &temp);
	}

	printf ("STACK: %s have %lu elements, they are:\n", idsl_stack_get_name(s), idsl_stack_get_size(s));
	
	for (i = 0; i < COUNT; i++){
		another_temp = (struct _stack_element_type *)idsl_stack_get_top(s);
		printf ("a = %d, b = %d\n", another_temp->a, another_temp->b);
		free(idsl_stack_pop(s));
	}

	if (idsl_stack_is_empty(s))
		printf("OK, now the stack is empty\n");


	idsl_stack_free (s);

	return 0;
}
