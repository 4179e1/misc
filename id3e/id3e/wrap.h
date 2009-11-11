#ifndef _WRAP_H
#define _WRAP_H

#include <gtk/gtk.h>
#include <stdio.h>

GObject *Gtk_builder_get_object (GtkBuilder *builder, const gchar *name);

FILE *Fopen (const char *filename, const char *mode);
int Fclose (FILE *stream);
int Fseek (FILE *stream, long offset, int orgin);

#endif /* _WRAP_H */
