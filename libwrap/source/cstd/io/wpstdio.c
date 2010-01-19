#include <stdio.h>
#include <stdlib.h>
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

long wp_ftell (FILE *fp)
{
	long n;
	if ((n = ftell (fp)) == -1L)
		wp_error_warning ("ftell error");
	return n;
}

int wp_fseek (FILE *fp, long offset, int whence)
{
	int n;
	if ((n = fseek (fp, offset, whence)) != 0)
		wp_error_warning ("fseek error");
	return n;
}

off_t wp_ftello (FILE *fp)
{
	off_t n;
	if ((n = ftello (fp)) == -1)
		wp_error_warning ("ftello error");
	return n;
}

int wp_fseeko (FILE *fp, off_t offset, int whence)
{
	int n;
	if ((n = fseeko (fp, offset, whence)) !=0)
		wp_error_warning ("fseeko error");
	return n;
}

int wp_fgetpos (FILE *fp, fpos_t *pos)
{
	int n;
	if ((n = fgetpos (fp, pos)) != 0)
		wp_error_warning ("fgetpos error");
	return n;
}

int wp_fsetpos (FILE *fp, fpos_t *pos)
{
	int n;
	if ((n = fsetpos (fp, pos)) != 0)
		wp_error_warning ("fsetpos error");
	return n;
}

int wp_vprintf (const char *fmt, va_list arg)
{
	int n;
	if ((n = wp_vprintf (fmt, arg)) < 0)
		wp_error_warning ("vprintf error");
	return n;
}

int wp_vfprintf (FILE *fp, const char *fmt, va_list arg)
{
	int n;
	if ((n = vfprintf (fp, fmt, arg)) < 0)
		wp_error_warning ("vfprintf error");
	return n;
}

int wp_vsprintf (char *buf, const char *fmt, va_list arg)
{
	int n;
	if ((n = vsprintf (buf, fmt, arg)) < 0)
		wp_error_warning ("vsprintf error");
	return n;
}

int wp_vsnprintf (char *buf, size_t n, const char *fmt, va_list arg)
{
	int i;
	if ((i = vsnprintf (buf, n, fmt, arg)) < 0)
		wp_error_warning ("vsnprintf error");
	return i;
}

int wp_vscanf (const char *format, va_list arg)
{
	int n;
	if ((n = vscanf (format, arg)) < 0)
		wp_error_warning ("vscanf error");
	return n;
}

int wp_vfscanf (FILE *fp, const char *fmt, va_list arg)
{
	int n;
	if ((n = vfscanf (fp, fmt, arg)) < 0)
		wp_error_warning ("vfscanf error");
	return n;
}

int wp_vsscanf (const char *buf, const char *fmt, va_list arg)
{
	int n;
	if ((n = vsscanf (buf, fmt, arg)) < 0)
		wp_error_warning ("vsscanf error");
	return n;
}

FILE *wp_tmpfile (void)
{
	FILE *file;
	if ((file = tmpfile ()) == NULL)
		wp_error_warning ("tmpfile error");
	return file;
}

int wp_mkstemp (char *template)
{
	int n;
	if ((n = mkstemp (template)) == -1)
		wp_error_warning ("mkstemp error");
	return n;
}


FILE *wp_popen (const char *cmdstring, const char *type)
{
	FILE *fp;
	if ((fp = popen (cmdstring, type)) == NULL)
		wp_error_warning ("popen() error");
	return fp;
}

int wp_pclose (FILE *fp)
{
	int n;
	if ((n = pclose (fp)) == -1)
		wp_error_warning ("pclose() error");
	return n;
}
