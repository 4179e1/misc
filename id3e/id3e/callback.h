#ifndef _CALLBACK_H
#define _CALLBACK_H

#include <gtk/gtk.h>
#include "id3e.h"

void on_liststore_insert (gpointer *widget, Id3e *id3e);
void on_liststore_delete (gpointer *widget, Id3e *id3e);
void on_liststore_open (gpointer *widget, Id3e *id3e);
void on_liststore_clear (gpointer *widget, Id3e *id3e);

void on_sidebar_toggle (gpointer *widget, Id3e *id3e);

void on_statusbar_toggle (gpointer *widget, Id3e *id3e);

gboolean on_query_tooltip (GtkWidget *widget, gint x, gint y, gboolean keyboard_mode, GtkTooltip *tooltip, Id3e *id3e);
#endif /* _CALLBACK_H */
