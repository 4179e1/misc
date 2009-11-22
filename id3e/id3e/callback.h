#ifndef _CALLBACK_H
#define _CALLBACK_H

#include <gtk/gtk.h>
#include "id3e.h"

void on_sidebar_toggle (gpointer *widget, Id3e *id3e);
void on_statusbar_toggle (gpointer *widget, Id3e *id3e);

void on_secondary_icon_press (GtkEntry *entry, GtkEntryIconPosition icon_pos, GdkEvent *event, Id3e *id3e);

void on_edit_clicked (GtkButton *button, Id3e *id3e);
void on_save_clicked (GtkButton *button, Id3e *id3e);
void on_enc_changed (GtkComboBox *combo, Id3e *id3e);
void on_enc_activate (GtkEntry *entry, Id3e *id3e);
void on_convert_clicked (GtkButton *button, Id3e *id3e);
#endif /* _CALLBACK_H */
