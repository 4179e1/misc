#ifndef _LIST_H
#define _LIST_H

#include <gtk/gtk.h>
#include "id3e.h"

void on_selection_changed (GtkTreeSelection *selection, Id3e *id3e);
void on_list_insert (gpointer *widget, Id3e *id3e);
void on_list_delete (gpointer *widget, Id3e *id3e);
void on_list_open (gpointer *widget, Id3e *id3e);
void on_list_clear (gpointer *widget, Id3e *id3e);
gboolean on_query_tooltip (GtkWidget *widget, gint x, gint y, gboolean keyboard_mode, GtkTooltip *tooltip, Id3e *id3e);

#endif /* _LIST_H */
