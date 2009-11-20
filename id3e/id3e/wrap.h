#ifndef _WRAP_H
#define _WRAP_H

#include <gtk/gtk.h>
#include <stdio.h>

#define FILE_MODE "rb+"
#define DUMP_MODE "wb+"

GObject *Gtk_builder_get_object (GtkBuilder *builder, const gchar *name);
gchar *G_convert (const gchar *str, gssize len,
		const gchar *to_codeset, const gchar *from_codeset,
		gsize *bytes_read, gsize *bytes_written);

FILE *G_fopen (const char *filename, const char *mode);
int Fclose (FILE *stream);
int Fseek (FILE *stream, long offset, int orgin);
long Ftell (FILE *file);

/* Exactly file read/write */
gboolean Efread (void *ptr, size_t size, size_t nobject, FILE *stream);
gboolean Efwrite (const void *ptr, size_t size, size_t nobject, FILE *stream);

#endif /* _WRAP_H */
