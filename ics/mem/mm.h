#ifndef MM_H
#define MM_H
#include <stdio.h>
#include <stdbool.h>
bool mm_init (void);
void *mm_malloc (size_t size);
void mm_free (void *bp);
#endif /* MM_H */
