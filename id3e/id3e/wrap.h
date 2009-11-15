#ifndef _WRAP_H
#define _WRAP_H

#include <gtk/gtk.h>
#include <stdio.h>

GObject *Gtk_builder_get_object (GtkBuilder *builder, const gchar *name);

FILE *G_fopen (const char *filename, const char *mode);
int Fclose (FILE *stream);
int Fseek (FILE *stream, long offset, int orgin);
int Fgetpos (FILE *stream, fpos_t *ptr);

/* Exactly file read/write */
gboolean Efread (void *ptr, size_t size, size_t nobject, FILE *stream);
gboolean Efwrite (const void *ptr, size_t size, size_t nobject, FILE *stream);

#endif /* _WRAP_H */
