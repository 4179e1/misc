#ifndef LIBMEM_H
#define LIBMEM_H
void mem_init (unsigned int size);
void *mem_sbrk (unsigned int incr);
#endif /* LIBMEM_H */
