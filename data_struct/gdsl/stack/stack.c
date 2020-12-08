#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gdsl.h>

#define COUNT 10

struct _stack_element_type {
	int a;
	int b;
};

gdsl_element_t stack_alloc (void *user_data) {
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

	return (gdsl_element_t)astack_element;
}

void stack_free (gdsl_element_t E) {
	if (E != NULL)
		free(E);
	return;
}

int main( void ) {
	struct _stack_element_type temp;
	struct _stack_element_type *another_temp;
	gdsl_stack_t astack;
	astack = gdsl_stack_alloc ("a test stack", stack_alloc, stack_free);

	int i;
	for (i = 0; i < COUNT; i++){
		temp.a = i;
		temp.b = i;

		gdsl_stack_insert (astack, &temp);
	}

	printf ("STACK: %s have %u elements, they are:\n", gdsl_stack_get_name(astack), gdsl_stack_get_size(astack));
	
	for (i = 0; i < COUNT; i++){
		another_temp = (struct _stack_element_type *)gdsl_stack_get_top(astack);
		gdsl_stack_remove(astack);
		printf ("a = %d, b = %d\n", another_temp->a, another_temp->b);
	}

	if (gdsl_stack_is_empty(astack))
		printf("OK, now the stack is empty\n");

	gdsl_stack_free (astack);
	return 0;
}
