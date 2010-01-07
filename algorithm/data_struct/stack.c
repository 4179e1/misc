#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _stack
{
	void **data;
	int growing_factor;
	int size;
	int card;
};

Stack *stack_new (int size)
{
	Stack *s;
	assert (size > 0);

	s = (Stack *)Malloc (sizeof (Stack));
	if (s == NULL)
	{
		return NULL;
	}

	s->data = (void **)Malloc (sizeof (void*) * size);
	if (s->data == NULL)
	{
		free (s);
		return NULL;
	}

	s->growing_factor = 10;
	s->size = size;
	s->card = 0;

	return s;
}

void stack_free (Stack *s)
{
	assert (s != NULL);
	free (s->data);
	free (s);
}

void stack_flush (Stack *s)
{
	assert (s != NULL);
	s->card = 0;
}

bool stack_is_empty (const Stack *s)
{
	assert (s != NULL);
	return (s->card == 0);
}

int stack_get_size (const Stack *s)
{
	assert (s != NULL);
	return s->size;
}

int stack_get_card (const Stack *s)
{
	assert (s != NULL);
	return s->card;
}

int stack_get_growing_factor (const Stack *s)
{
	assert (s != NULL);
	return s->growing_factor;
}

void stack_set_growing_factor (Stack *s, int value)
{
	assert (s != NULL);
	s->growing_factor = value;
}

void stack_push (Stack *s, void *data)
{
	assert (s != NULL);

	(s->card++);
	if ((s->card) == (s->size))
	{
		s->data = Realloc (s->data, (s->size) + (s->growing_factor));
		if (s->data == NULL)
		{
			return;
		}
		s->size += s->growing_factor;
	}
	s->data[s->card - 1] = (void *)data;
}

void *stack_pop (Stack *s)
{
	if (s->card == 0)
	{
		fprintf (stderr, "Stack is empty\n");
		return NULL;
	}
	(s->card)--;
	return s->data[s->card];
}

void *stack_top (const Stack *s)
{
	if (s->card == 0)
	{
		fprintf (stderr, "Stack is empty\n");
		return NULL;
	}
	return s->data[s->card - 1];
}

void stack_dump (const Stack *s, FILE *file, write_func_t f, void *data)
{
	int i;
	fprintf (file, "<STACK SIZE=\"%d\" CARD=\"%d\" GROWING_FACTOR=\"%d\">", s->size, s->card, s->growing_factor);
	for (i = 0; i < (s->card); i++)
	{
		fprintf (file, "<NODE CONTENT=\"%p\">", s->data[i]);
		if (f)
		{
			f(s->data[i], file, data);
		}
		fprintf (file, "</NODE>");
	}
	fprintf (file, "</STACK>\n");
}

void stack_foreach (const Stack *s, foreach_func_t f, void *data)
{
	int i;
	for (i = 0; i < (s->card); i++)
	{
		if (f (s->data[i], data) == false)
		{
			break;
		}
	}
}
