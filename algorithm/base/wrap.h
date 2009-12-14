#ifndef _WRAP_H
#define _WRAP_H
#include <stdio.h>

void *Malloc (size_t size);
void *Calloc (size_t count, size_t size);
void *Realloc (void *ptr, size_t size);

#endif /* _WRAP_H */
