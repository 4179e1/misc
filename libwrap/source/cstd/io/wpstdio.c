#include <stdio.h>
#include "wpstdio.h"
#include "wpbase.h"

int wp_fclose (FILE *fp)
{
	int n;
	if ((n = fclose (fp)) == EOF)
		wp_error_warning ("fclose error");
	return n;
}

FILE *wp_fdopen (int filedes, const char *type)
{
	FILE *file;
	if ((file = fdopen (filedes, type)) == NULL)
		wp_error_warning ("fdopen error");
	return file;
}

int wp_fgetc (FILE *fp)
{
	int n;
	clearerr (fp);
	n = fgetc (fp);
	if (n == EOF && ferror (fp) == 0)
		wp_error_warning ("fgetc error");
	return n;
}

char *wp_fgets (char *buf, int n, FILE *fp)
{
	char *str;
	if ((str = fgets (buf, n, fp)) == NULL)
		wp_error_warning ("fgets error");
	return str;
}

int wp_fputc (int c, FILE *fp)
{
	int n;
	if ((n = fputc (c, fp)) == EOF)
		wp_error_warning ("fputc error");
	return n;
}

int wp_fputs (const char *str, FILE *fp)
{
	int n;
	if ((n = fputs (str, fp)) == EOF)
		wp_error_warning ("fputs error");
	return n;
}

int wp_fflush (FILE *fp)
{
	int n;
	if ((n = fflush (fp)) == EOF)
		wp_error_warning ("fflush error");
	return n;
}

FILE *wp_fopen (const char *path, const char *type)
{
	FILE *file;
	if ((file = fopen (path, type)) == NULL)
		wp_error_warning ("fopen error");
	return file;
}

size_t wp_fread (void *ptr, size_t size, size_t nobj, FILE *fp)
{
	size_t n;

	clearerr (fp);
	n = fread (ptr, size, nobj, fp);
	if (ferror (fp) == 0)
		wp_error_warning ("fread error");
	return n;
}

FILE *wp_freopen (const char *pathname, const char *type, FILE *fp)
{
	FILE *file;
	if ((file = freopen (pathname, type, fp)) == NULL)
		wp_error_warning ("freopen error");
	return file;
}

int wp_getc (FILE *fp)
{
	int n;
	clearerr (fp);
	n = getc (fp);
	if (n == EOF && ferror(fp) == 0)
		wp_error_warning ("getc error");
	return n;
}

int wp_getchar (void)
{
	int n;
	clearerr (stdin);
	n = getchar ();
	if (n == EOF && ferror (stdin) == 0)
		wp_error_warning ("getchar error");
	return n;
}

int wp_putc (int c, FILE *fp)
{
	int n;
	if ((n = putc (c, fp)) == EOF)
		wp_error_warning ("putc error");
	return n;
}

int wp_putchar (int c)
{
	int n;
	if ((n = putchar (c)) == EOF)
		wp_error_warning ("putchar error");
	return n;
}

int wp_remove (const char *path)
{
	int n;
	if ((n = remove (path)) == -1)
		wp_error_warning ("remove error");
	return n;
}

int wp_rename (const char *oldname, const char *newname)
{
	int n;
	if ((n = rename (oldname, newname)) == -1)
		wp_error_warning ("rename error");
	return n;
}

int wp_setvbuf (FILE *fp, char *buf, int mode, size_t size)
{
	int n;
	if ((n = setvbuf (fp, buf, mode, size)) != 0)
		wp_error_warning ("setvbuf error");
	return n;
}

int wp_ungetc (int c, FILE *fp)
{
	int n;
	if ((n = ungetc (c, fp)) == EOF)
		wp_error_warning ("ungetc error");
	return n;
}

size_t wp_fwrite (const void *ptr, size_t size, size_t nobj, FILE *fp)
{
	int n;
	clearerr (fp);
	n = fwrite (ptr, size, nobj, fp);
	if (ferror (fp) == 0)
		wp_error_warning ("fwrite error");
	return n;
}