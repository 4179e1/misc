/**
 * Yesterday i had a job interview, the examier asked me to write a queue
 * with enqueue & dequeue operation. Ater serval minutes, I said I can't 
 * finish it in such a short time.
 *		"It's it very difficult?"
 *		"No."
 * I didn't say more. How would they think a queue wrote in 5 minutes have
 * any usability? It may explosive at any second. I could worte a complete
 * and safe queue in 2 hour, but not one uncomplete & unsafe in 5 minutes.
 */

#ifndef _QUEUE_H
#define _QUEUE_H
#include <stdbool.h>
#include "base.h"

typedef struct _queue Queue;

Queue *queue_new(int size);
void queue_free (Queue *q);
void queue_flush (Queue *q);

bool queue_is_empty (const Queue *q);
int queue_get_size (const Queue *q);
int queue_get_card (const Queue *q);
int queue_get_growing_factor (const Queue *q);
void queue_set_growing_factor (Queue *q, int value);

void queue_push_head (Queue *q, void *data);
void queue_push_tail (Queue *q, void *data);
void *queue_head (const Queue *q);
void *queue_tail (const Queue *q);
void *queue_pop_head (Queue *q);
void *queue_pop_tail (Queue *q);

void queue_dump (const Queue *q, FILE *file, write_func_t f, void *data);
void queue_foreach (const Queue *q, foreach_func_t f, void *data);

#endif /* _QUEUE_H */
