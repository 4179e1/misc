#ifndef _WPSTDSYS_H
#define _WPSTDSYS_H

#include <time.h>

time_t wp_time (time_t *calptr);
time_t wp_mktime (struct tm *tmptr);

int wp_atexit (void (*func) (void));
#endif /* _WPSTDSYS_H */
