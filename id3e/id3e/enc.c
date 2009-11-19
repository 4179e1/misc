#include <gtk/gtk.h>
#include "enc.h"
#include "gv1.h"
#include "wrap.h"
#include "callback.h"

struct _enc
{
	GtkWidget *src;
	GtkWidget *dest;
	GtkListStore *store;
	Gv1 *gv1;
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

	{
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

		GtkEntry *entry;
		entry = GTK_ENTRY (GTK_BIN (enc->dest)->child);
		g_signal_connect (entry, "activate", G_CALLBACK (on_enc_editing_done), NULL);

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

gchar *enc_get_src (Enc *enc)
{
	gchar *codeset = NULL;
	GtkTreeIter iter;
	
	if (gtk_combo_box_get_active_iter (GTK_COMBO_BOX (enc->src), &iter))
	{
		gtk_tree_model_get (GTK_TREE_MODEL (enc->store), &iter, 0, &codeset, -1);
	}

	return codeset;
}

gchar *enc_get_dest (Enc *enc)
{
	gchar *codeset = NULL;
	GtkTreeIter iter;

	if (gtk_combo_box_get_active_iter (GTK_COMBO_BOX (enc->dest), &iter))
	{
		gtk_tree_model_get (GTK_TREE_MODEL (enc->store), &iter, 0, &codeset, -1);
	}

	return codeset;
}

gchar *enc_set_src (Enc *enc, gchar *codeset)
{
	return codeset;
}

gchar *enc_set_dest (Enc *enc, gchar *codeset)
{
	return codeset;
}
