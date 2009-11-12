#include <gtk/gtk.h>
#include <stdio.h>
#include "wrap.h"

GObject *Gtk_builder_get_object (GtkBuilder *builder, const gchar *name)
{
	GObject *obj;

	if ((obj = gtk_builder_get_object (builder, name)) == NULL)
	{
		g_warning ("gtk_builder_get_object: %s failed!", name);
	}

	return obj;
}

FILE *Fopen (const char *filename, const char *mode)
{	FILE *file;
	if ((file = fopen (filename, mode)) == NULL)
	{
		g_warning ("fopen error");
	}

	return file;
}

int Fclose (FILE *stream)
{
	int status;
	if ((status = fclose (stream)) == EOF)
	{
		g_warning ("flose error");
	}
	return status;
}

int Fseek (FILE *stream, long offset, int orgin)
{
	int result;
	if ((result = fseek (stream, offset, orgin)) != 0)
	{
		g_warning ("fseek error: %d", result);
	}
	return result;
}

gboolean Efread (void *ptr, size_t size, size_t nobject, FILE *stream)
{
	size_t n;
	if ((n = fread (ptr, size, nobject, stream)) != size)
	{
		g_warning ("fread error: Request to read %d bytes, but %d bytes actually readed", size, n);
		return FALSE;
	}
	return TRUE;
}

gboolean Ewrite (const void *ptr, size_t size, size_t nobject, FILE *stream)
{
	size_t n;
	if ((n = fwrite (ptr, size, nobject, stream)) != size)
	{
		g_warning ("fwrite error: Request to write %d bytes, but %d bytes actually wrote", size, n);
		return FALSE;
	}
	return TRUE;
}
