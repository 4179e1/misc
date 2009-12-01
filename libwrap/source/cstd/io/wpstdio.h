#ifndef _WPSTDIO_H
#define _WPSTDIO_H

#include <stdio.h>

int wp_fclose (FILE *fp);
FILE *wp_fdopen (int filedes, const char *type);
int wp_fgetc (FILE *fp);
char *wp_fgets (char *buf, int n, FILE *fp);
int wp_fputc (int c, FILE *fp);
int wp_fputs (const char *str, FILE *fp);
int wp_fflush (FILE *fp);
FILE *wp_fopen (const char *pathname, const char *type);
size_t wp_fread (void *ptr, size_t size, size_t nobj, FILE *fp);
FILE *wp_freopen (const char *pathname, const char *type, FILE *fp);
int wp_getc (FILE *fp);
int wp_getchar (void);
int wp_putc (int c, FILE *fp);
int wp_putchar (int c);
int wp_remove (const char *pathname);
int wp_rename (const char *oldname, const char *newname);
int wp_setvbuf (FILE *fp, char *buf, int mode, size_t size);
int wp_ungetc (int c, FILE *fp);
size_t wp_fwrite (const void *ptr, size_t size, size_t nobj, FILE *fp);

#endif /* _WPSTDIO_H */
