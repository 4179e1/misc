#include <gtk/gtk.h>
#include "gv1.h"
#include "genre.h"
#include "wrap.h"

gboolean gv1_init (GtkBuilder *builder)
{
	GtkListStore *liststore;

	liststore = GTK_LIST_STORE (
			Gtk_builder_get_object (builder, "genre_list"));
	
	genre_list_init (liststore);
	return TRUE;
}
