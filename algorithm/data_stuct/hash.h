#ifndef _HASH_H
#define _HASH_H

#include <stdio.h>
#include <stdbool.h>
#include "base.h"

typedef int (*key_func_t)(void *data);

typedef struct _hash Hash;

Hash *hash_new (int size, key_func_t key_f, compare_func_t cmp_f);
void key_free (Hash *h);
void key_flush (Hash *h);

bool hash_is_empty (const Hash *h);
int hash_get_card (const Hash *h);
int hash_get_growing_factor (const Hash *h);

void hash_set_growing_factor (Hash *h, int value);
void hash_set_compare_func (Hash *h, compare_func_t cmp_f);

void hash_insert (Hash *h, void *data);
void *hash_search (const Hash *h, void *data);
void *hash_delete (Hash *h, void *data);

void hash_dump (const Hash *h, FILE *file, write_func_t f);
void key_foreach (Hash *h, foreach_func_t f, void *data);

int sum_hash (void *data, int len);
#endif /* _HASH_H */
