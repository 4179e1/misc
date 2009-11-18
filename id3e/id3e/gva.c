#include <gtk/gtk.h>
#include "gva.h"
#include "gv1.h"
#include "wrap.h"

struct _gva
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

Gva *gva_new (void)
{
	return g_new (Gva, 1);
}

void gva_free (Gva *gva)
{
	g_free (gva);
}

Gva *gva_init (Gva *gva, GtkBuilder *builder)
{
	gva->src = GTK_WIDGET (Gtk_builder_get_object (builder, "gva_src"));
	gva->dest = GTK_WIDGET (Gtk_builder_get_object (builder, "gva_dest"));
	gva->store = gtk_list_store_new (1, G_TYPE_STRING);

	{
		GtkTreeIter iter;
		gchar **ptr;

		for (ptr = charset_list; *ptr != NULL; ptr++)
		{
			gtk_list_store_append (gva->store, &iter);
			gtk_list_store_set (gva->store, &iter, 0, *ptr, -1);
		}

		gtk_combo_box_set_model (GTK_COMBO_BOX (gva->src),
				GTK_TREE_MODEL (gva->store));
		gtk_combo_box_entry_set_text_column (GTK_COMBO_BOX_ENTRY (gva->src), 0);
		gtk_combo_box_set_active (GTK_COMBO_BOX (gva->src), 0);

		gtk_combo_box_set_model (GTK_COMBO_BOX (gva->dest),
				GTK_TREE_MODEL (gva->store));
		gtk_combo_box_entry_set_text_column (GTK_COMBO_BOX_ENTRY (gva->dest), 0);
	}

	return gva;
}
