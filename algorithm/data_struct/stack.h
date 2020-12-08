#ifndef _STACK_H
#define _STACK_H

#include <stdio.h>
#include <stdbool.h>
#include "base.h"

typedef struct _stack Stack;

Stack *stack_new (int size);
void stack_free (Stack *s);
void stack_flush (Stack *s);

bool stack_is_empty (const Stack *s);
int stack_get_size (const Stack *s);
int stack_get_card (const Stack *s);
int stack_get_growing_factor (const Stack *s);
void stack_set_growing_factor (Stack *s, int value);

void stack_push (Stack *stack, void *data);
void *stack_pop (Stack *stack);
void *stack_top (const Stack *stack);

void stack_dump (const Stack *s, FILE *file, write_func_t f, void *data);
void stack_foreach (const Stack *s, foreach_func_t f, void *data);

#endif /* _STACK_H */
