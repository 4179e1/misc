#ifndef _WPSTDIO_H
#define _WPSTDIO_H

#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

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

long wp_ftell (FILE *fp);
int wp_fseek (FILE *fp, long offset, int whence);
off_t wp_ftello (FILE *fp);
int wp_fseeko (FILE *fp, off_t offset, int whence);
int wp_fgetpos (FILE *fp, fpos_t *pos);
int wp_fsetpos (FILE *fp, fpos_t *pos);

int wp_vprintf (const char *fmt, va_list arg);
int wp_vfprintf (FILE *fp, const char *fmt, va_list arg);
int wp_vsprintf (char *buf, const char *fmt, va_list arg);
int wp_vsnprintf (char *buf, size_t n, const char *fmt, va_list arg);

int wp_vscanf (const char *format, va_list arg);
int wp_vfscanf (FILE *fp, const char *fmt, va_list arg);
int wp_vsscanf (const char *buf, const char *fmt, va_list arg);

FILE *wp_tmpfile (void);
int wp_mkstemp (char *template);
#endif /* _WPSTDIO_H */
