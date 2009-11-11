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
