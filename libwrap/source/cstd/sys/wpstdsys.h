#ifndef _WPSTDSYS_H
#define _WPSTDSYS_H

#include <time.h>

time_t wp_time (time_t *calptr);
time_t wp_mktime (struct tm *tmptr);

int wp_atexit (void (*func) (void));

void *wp_malloc (size_t size);
void *wp_calloc (size_t nobj, size_t size);
void *wp_realloc (void *ptr, size_t newsize);

char *wp_getenv (const char *name);
int wp_putenv (char *str);
int wp_setenv (const char *name, const char *value, int rewrite);
int wp_unsetenv (const char *name);

#endif /* _WPSTDSYS_H */
