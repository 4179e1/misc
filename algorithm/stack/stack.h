#ifndef _STACK_H
#define _STACK_H

#include <stdio.h>
#include <stdbool.h>
#include "base.h"

typedef struct _stack Stack;

Stack *stack_new (int size);
void stack_free (Stack *s);
void stack_flush (Stack *s);

bool stack_is_empty (Stack *s);
int stack_get_size (Stack *s);
int stack_get_card (Stack *s);
int stack_get_growing_factor (Stack *s);
void stack_set_growing_factor (Stack *s, int value);

void stack_push (Stack *stack, void *data);
void *stack_pop (Stack *stack);
void *stack_top (Stack *stack);

void stack_dump (Stack *s, FILE *file);
void stack_foreach (Stack *s, foreach_func_t f, void *data);

#endif /* _STACK_H */
