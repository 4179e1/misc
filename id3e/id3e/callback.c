#include <gtk/gtk.h>
#include "id3e.h"
#include "callback.h"

#include <string.h>

G_MODULE_EXPORT 
void on_sidebar_toggle (gpointer *widget, Id3e *id3e)
{
	id3e_sidebar_toggle (id3e);
}

G_MODULE_EXPORT 
void on_statusbar_toggle (gpointer *widget, Id3e *id3e)
{
	id3e_statusbar_toggle (id3e);
}

G_MODULE_EXPORT
void on_edit_clicked (GtkButton *button, Id3e *id3e)
{
	Gva *gva = id3e_get_gva (id3e);
	if (id3e_list_get_selected_count (id3e) == 0)
	{
		gva_set_sensitive (gva, FALSE);
		return;
	}
	gva_set_sensitive (gva, !gva_is_sensitive (gva));
}

G_MODULE_EXPORT
void on_save_clicked (GtkButton *button, Id3e *id3e)
{
	g_message ("on_save_clicked");
}

G_MODULE_EXPORT
void on_enc_changed (GtkComboBox *combo, Id3e *id3e)
{
	gint index;
	g_message ("on_enc_changed");
	if ((index = gtk_combo_box_get_active (combo)) == -1)
	{
		g_message ("ok, nothing active");
		return;
	}
	/* TODO: refresh gva/id3 */
}

G_MODULE_EXPORT
void on_convert_clicked (GtkButton *button, Id3e *id3e)
{
	g_message ("on_convert_clicked");
}

G_MODULE_EXPORT
void on_secondary_icon_press (GtkEntry *entry, GtkEntryIconPosition icon_pos, GdkEvent *event, Id3e *id3e)
{
	if (icon_pos == GTK_ENTRY_ICON_SECONDARY)
	{
		/* clear text */
		gtk_entry_set_text (entry, "");
	}
}
