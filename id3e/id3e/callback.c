#include <gtk/gtk.h>
#include "id3e.h"
#include "callback.h"
#include "list.h"

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
void on_secondary_icon_press (GtkEntry *entry, GtkEntryIconPosition icon_pos, GdkEvent *event, Id3e *id3e)
{
	if (icon_pos == GTK_ENTRY_ICON_SECONDARY)
	{
		/* clear text */
		gtk_entry_set_text (entry, "");
	}
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

	gint selected_num;
	Gva *gva;
	Enc *enc;

	selected_num = id3e_list_get_selected_count (id3e);
	gva = id3e_get_gva (id3e);
	enc = id3e_get_enc (id3e);

	if (selected_num == 0)
	{
		return;
	}
	else
	{
		GList *list;
		GList *ptr;
		GtkTreeModel *model;
		GtkTreeIter iter;
		gchar *path = NULL;
		gchar *src;

		src = enc_get_src_text (enc);
		model = GTK_TREE_MODEL (id3e_get_list_store (id3e));
		list = id3e_list_get_selected_rows (id3e);
		ptr = list;

		if (selected_num == 1)
		{
			if (gtk_tree_model_get_iter (model, &iter, (GtkTreePath *)ptr->data))
			{
				Id3 *tag;
				Id3 *id3_new;
				gboolean result;

				gtk_tree_model_get (model, &iter, 1, &path, -1);
				
				tag = id3_new_with_tag ();
				gva_write_to_id3 (gva, tag);

				id3_new = id3_convert (tag, src, "UTF-8", &result);

				id3_write_tag_to_path (id3_new, path);

				id3_free (id3_new);
				id3_free (tag);
				g_free (path);
			}
		}
		else
		{
		}

		g_free (src);

		g_list_foreach (list, (GFunc)gtk_tree_path_free, NULL);
		g_list_free (list);
	}
}

G_MODULE_EXPORT
void on_enc_changed (GtkComboBox *combo, Id3e *id3e)
{
	gint index;
	if ((index = gtk_combo_box_get_active (combo)) == -1)
	{
		return;
	}
	on_selection_changed (id3e_list_get_selection (id3e) , id3e);
}

G_MODULE_EXPORT
void on_enc_activate (GtkEntry *entry, Id3e *id3e)
{
	g_message ("on_enc_activate");
	on_selection_changed (id3e_list_get_selection (id3e) , id3e);
}

G_MODULE_EXPORT
void on_convert_clicked (GtkButton *button, Id3e *id3e)
{
	g_message ("on_convert_clicked");
		gint selected_num;
	Gva *gva;
	Enc *enc;

	selected_num = id3e_list_get_selected_count (id3e);
	gva = id3e_get_gva (id3e);
	enc = id3e_get_enc (id3e);

	if (selected_num == 0)
	{
		return;
	}
	else
	{
		GList *list;
		GList *ptr;
		GtkTreeModel *model;
		GtkTreeIter iter;
		gchar *path = NULL;
		gchar *src;
		gchar *dest;

		src = enc_get_src_text (enc);
		dest = enc_get_dest_text (enc);
		model = GTK_TREE_MODEL (id3e_get_list_store (id3e));
		list = id3e_list_get_selected_rows (id3e);
		ptr = list;

		if (selected_num == 1)
		{
			if (gtk_tree_model_get_iter (model, &iter, (GtkTreePath *)ptr->data))
			{
				gtk_tree_model_get (model, &iter, 1, &path, -1);
				/* TODO: convert codeset */
				g_free (path);
			}
		}
		else
		{
		}

		g_free (src);
		g_free (dest);

		g_list_foreach (list, (GFunc)gtk_tree_path_free, NULL);
		g_list_free (list);
	}

}
