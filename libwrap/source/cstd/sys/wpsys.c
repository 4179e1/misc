#include <stdlib.h>
#include "wpstdsys.h"
#include "wpbase.h"

time_t wp_time (time_t *calptr)
{
	time_t t;
	if ((t = time (calptr)) == -1)
		wp_error_warning ("time error");
	return t;
}

time_t wp_mktime (struct tm *tmptr)
{
	time_t t;
	if ((t = mktime (tmptr)) == -1)
		wp_error_warning ("mktime error");
	return t;
}

int wp_atexit (void (*func) (void))
{
	int n;
	if ((n = atexit (func)) != 0)
		wp_error_warning ("atexit error");
	return n;
}

void *wp_malloc (size_t size)
{
	void *ptr;
	if ((ptr = malloc (size)) == NULL)
		wp_error_warning ("malloc error");
	return ptr;
}

void *wp_calloc (size_t nobj, size_t size)
{
	void *ptr;
	if ((ptr = calloc (nobj, size)) == NULL)
		wp_error_warning ("calloc error");
	return ptr;
}

void *wp_realloc (void *ptr, size_t newsize)
{
	void *p;
	if ((p = realloc (ptr, newsize)) == NULL)
		wp_error_warning ("realloc error");
	return p;
}

char *wp_getenv (const char *name)
{
	char *str;
	if ((str = getenv (name)) == NULL)
		wp_error_warning ("getenv error");
	return str;
}

int wp_putenv (char *str)
{
	int n;
	if ((n = putenv (str)) != 0)
		wp_error_warning ("putenv error");
	return n;
}

int wp_setenv (const char *name, const char *value, int rewrite)
{
	int n;
	if ((n = setenv (name, value, rewrite)) != 0)
		wp_error_warning ("setenv error");
	return n;
}

int wp_unsetenv (const char *name)
{
	int n;
	if ((n = unsetenv (name)) != 0)
		wp_error_warning ("unsetenv error");
	return n;
}

