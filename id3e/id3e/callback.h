#ifndef _CALLBACK_H
#define _CALLBACK_H

#include <gtk/gtk.h>
#include "id3e.h"

void on_selection_changed (GtkTreeSelection *selection, Id3e *id3e);
void on_list_insert (gpointer *widget, Id3e *id3e);
void on_list_delete (gpointer *widget, Id3e *id3e);
void on_list_open (gpointer *widget, Id3e *id3e);
void on_list_clear (gpointer *widget, Id3e *id3e);

void on_sidebar_toggle (gpointer *widget, Id3e *id3e);
void on_statusbar_toggle (gpointer *widget, Id3e *id3e);

gboolean on_query_tooltip (GtkWidget *widget, gint x, gint y, gboolean keyboard_mode, GtkTooltip *tooltip, Id3e *id3e);

void on_edit_clicked (gpointer *widget, Id3e *id3e);
void on_save_clicked (gpointer *widget, Id3e *id3e);
void on_enc_changed (gpointer *widget, Id3e *id3e);
void on_enc_editing_done (GtkCellEditable *celleditable, Id3e *id3e);
void on_convert_clicked (gpointer *widget, Id3e *id3e);

#endif /* _CALLBACK_H */
