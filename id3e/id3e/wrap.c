#include <gtk/gtk.h>
#include <glib/gstdio.h>
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

gchar *G_convert (const gchar *str, gssize len, const gchar *to_codeset,
		const gchar *from_codeset, gsize *bytes_read,
		gsize *bytes_written)
{
	gchar *ptr;
	GError *error = NULL;
	ptr = g_convert (str, len, to_codeset, from_codeset,
			bytes_read, bytes_written, &error);
	if (error != NULL)
	{
		g_warning ("%s", error->message);
		g_message ("%u reade, %u written", *bytes_read, *bytes_written);
		g_free (error);
	}
	return ptr;
}

FILE *G_fopen (const char *filename, const char *mode)
{	FILE *file;
	if ((file = g_fopen (filename, mode)) == NULL)
	{
		g_warning ("g_fopen error");
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

long Ftell (FILE *file)
{
	long len;
	if ((len = ftell (file)) == -1)
	{
		g_warning ("ftell error");
	}

	return len;
}

gboolean Efread (void *ptr, size_t size, size_t nobject, FILE *stream)
{
	size_t n;
	if ((n = fread (ptr, size, nobject, stream)) != nobject)
	{
		g_warning ("fread error: Request to read %d bytes, but %d bytes actually readed", size, n);
		return FALSE;
	}
	return TRUE;
}

gboolean Efwrite (const void *ptr, size_t size, size_t nobject, FILE *stream)
{
	size_t n;
	if ((n = fwrite (ptr, size, nobject, stream)) != nobject)
	{
		g_warning ("fwrite error: Request to write %d bytes, but %d bytes actually wrote", size, n);
		return FALSE;
	}
	return TRUE;
}
