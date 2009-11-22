#include <gtk/gtk.h>
#include <string.h>
#include "enc.h"
#include "wrap.h"
#include "callback.h"
#include "id3e.h"

/* set attribute for entry of combobox */
static void set_entry_attribute (Enc *enc, GtkEntry *entry);
/* callback func while click the icon in entry of combobox */
static void enc_icon_press (GtkEntry *entry, GtkEntryIconPosition icon_pos, GdkEvent *event, Enc *enc);
/* foreach func to find string in treemodel of combobox */
static gboolean enc_store_find (GtkTreeModel *model, GtkTreePath *path, GtkTreeIter *iter, Enc *enc);

struct _enc
{
	GtkWidget *src;
	GtkWidget *dest;
	GtkListStore *store;
	gboolean found;
	const gchar *to_find;
};

gchar *charset_list[] = 
{
	"UTF-8",
	"GBK",
	NULL,
};

Enc *enc_new (void)
{
	return g_new (Enc, 1);
}

void enc_free (Enc *enc)
{
	g_free (enc);
}

Enc *enc_init (Enc *enc, GtkBuilder *builder)
{
	enc->src = GTK_WIDGET (Gtk_builder_get_object (builder, "enc_src"));
	enc->dest = GTK_WIDGET (Gtk_builder_get_object (builder, "enc_dest"));
	enc->store = gtk_list_store_new (1, G_TYPE_STRING);
	enc->found = FALSE;
	enc->to_find = FALSE;

	{
		GtkEntry *entry;
		GtkTreeIter iter;
		gchar **ptr;

		for (ptr = charset_list; *ptr != NULL; ptr++)
		{
			gtk_list_store_append (enc->store, &iter);
			gtk_list_store_set (enc->store, &iter, 0, *ptr, -1);
		}

		gtk_combo_box_set_model (GTK_COMBO_BOX (enc->src),
				GTK_TREE_MODEL (enc->store));
		gtk_combo_box_entry_set_text_column (GTK_COMBO_BOX_ENTRY (enc->src), 0);

		gtk_combo_box_set_model (GTK_COMBO_BOX (enc->dest),
				GTK_TREE_MODEL (enc->store));
		gtk_combo_box_entry_set_text_column (GTK_COMBO_BOX_ENTRY (enc->dest), 0);

		/* src entry */
		entry = GTK_ENTRY (GTK_BIN (enc->src)->child);
		set_entry_attribute (enc, entry);
		/* dest entry */
		entry = GTK_ENTRY (GTK_BIN (enc->dest)->child);
		set_entry_attribute (enc, entry);

		enc_reset(enc);
	}

	return enc;
}

Enc *enc_reset (Enc *enc)
{
	gtk_combo_box_set_active (GTK_COMBO_BOX (enc->src), 0);
	gtk_combo_box_set_active (GTK_COMBO_BOX (enc->dest), -1);
	return enc;
}

GtkEntry *enc_get_src_entry (Enc *enc)
{
	return GTK_ENTRY (GTK_BIN (enc->src)->child);
}

GtkEntry *enc_get_dest_entry (Enc *enc)
{
	return GTK_ENTRY (GTK_BIN (enc->dest)->child);
}

GtkListStore *enc_get_list_store (Enc *enc)
{
	return enc->store;
}

/* directly text */
gchar *enc_get_src_text (Enc *enc)
{
	gchar *text;
	text = gtk_combo_box_get_active_text (GTK_COMBO_BOX (enc->src));
	return text;
}

gchar *enc_get_dest_text (Enc *enc)
{
	gchar *text;
	text = gtk_combo_box_get_active_text (GTK_COMBO_BOX (enc->dest));
	return text;
}

gchar *enc_set_src_text (Enc *enc, gchar *text)
{
	GtkEntry *entry;
	entry = GTK_ENTRY (GTK_BIN (enc->src)->child);
	gtk_entry_set_text (entry, text);
	return text;
}

gchar *enc_set_dest_text (Enc *enc, gchar *text)
{
	GtkEntry *entry;
	entry = GTK_ENTRY (GTK_BIN (enc->dest)->child);
	gtk_entry_set_text (entry, text);
	return text;
}

gchar *enc_get_src_active_text (Enc *enc)
{
	gchar *codeset = NULL;
	GtkTreeIter iter;
	
	if (gtk_combo_box_get_active_iter (GTK_COMBO_BOX (enc->src), &iter))
	{
		gtk_tree_model_get (GTK_TREE_MODEL (enc->store), &iter, 0, &codeset, -1);
	}

	return codeset;
}

gchar *enc_get_dest_active_text (Enc *enc)
{
	gchar *codeset = NULL;
	GtkTreeIter iter;

	if (gtk_combo_box_get_active_iter (GTK_COMBO_BOX (enc->dest), &iter))
	{
		gtk_tree_model_get (GTK_TREE_MODEL (enc->store), &iter, 0, &codeset, -1);
	}

	return codeset;
}

/* text in index */
gint enc_get_src_active (Enc *enc)
{
	return gtk_combo_box_get_active (GTK_COMBO_BOX (enc->src));
}

gint enc_get_dest_active (Enc *enc)
{
	return gtk_combo_box_get_active (GTK_COMBO_BOX (enc->dest));
}

gint enc_set_src_active (Enc *enc, gint index)
{
	gtk_combo_box_set_active (GTK_COMBO_BOX (enc->src), index);
	return index;
}
gint enc_set_dest_active (Enc *enc, gint index)
{
	gtk_combo_box_set_active (GTK_COMBO_BOX (enc->dest), index);
	return index;
}

/* text in iter */
gboolean enc_get_src_active_iter (Enc *enc, GtkTreeIter *iter)
{
	return gtk_combo_box_get_active_iter (GTK_COMBO_BOX (enc->src), iter);
}

gboolean enc_get_dest_active_iter (Enc *enc, GtkTreeIter *iter)
{
	return gtk_combo_box_get_active_iter (GTK_COMBO_BOX (enc->dest), iter);
}

void enc_set_src_active_iter (Enc *enc, GtkTreeIter *iter)
{
	gtk_combo_box_set_active_iter (GTK_COMBO_BOX (enc->src), iter);
}

void enc_set_dest_active_iter (Enc *enc, GtkTreeIter *iter)
{
	gtk_combo_box_set_active_iter (GTK_COMBO_BOX (enc->dest), iter);
}

/* private func */
static void enc_icon_press (GtkEntry *entry, GtkEntryIconPosition icon_pos, GdkEvent *event, Enc *enc)
{
	if (icon_pos == GTK_ENTRY_ICON_PRIMARY)
	{
		/* this string is in entry, should not be free or stroe */
		enc->to_find = gtk_entry_get_text (entry);
		if (*(enc->to_find) != '\0')
		{
			enc->found = FALSE;
			gtk_tree_model_foreach (GTK_TREE_MODEL (enc->store), (GtkTreeModelForeachFunc)enc_store_find, enc);
			if (!(enc->found))
			{
				/* TODO: add text to list */
				/* copy a string and add it to list */
				GtkTreeIter iter;
				gchar *to_insert = g_ascii_strup (enc->to_find, strlen (enc->to_find));

				gtk_list_store_append (enc->store, &iter);
				gtk_list_store_set (enc->store, &iter, 0, to_insert, -1);

				g_free (to_insert);
			}
		}
	}

	gtk_entry_set_text (entry, "");
}

static void set_entry_attribute (Enc *enc, GtkEntry *entry)
{
	gtk_entry_set_icon_from_stock (GTK_ENTRY (entry),
			GTK_ENTRY_ICON_PRIMARY, GTK_STOCK_ADD);
	gtk_entry_set_icon_from_stock (GTK_ENTRY (entry),
			GTK_ENTRY_ICON_SECONDARY, GTK_STOCK_CLEAR);
	g_signal_connect (entry, "icon-press", G_CALLBACK (enc_icon_press), (gpointer)enc);
	/* TODO: connect signals */
}

static gboolean enc_store_find (GtkTreeModel *model, GtkTreePath *path, GtkTreeIter *iter, Enc *enc)
{
	gchar *str;

	gtk_tree_model_get (model, iter, 0, &str, -1);
	/* FIXME: is case sensitive compare strcmp() a better choice? */
	if (g_ascii_strcasecmp (str, enc->to_find) == 0)
	{
		enc->found = TRUE;
	}

	g_free (str);
	/**
	 * using enc->found but not a dividual local variable,
	 * it require to set it to FALSE before.
	 */
	return enc->found;
}
