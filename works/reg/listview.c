#include <gtk/gtk.h>
#include "reg.h"
#include "listview.h"

GtkWidget* create_list_view_and_model (void) {
	GtkCellRenderer *renderer;
	GtkListStore *store;
	GtkWidget *view;

	view = gtk_tree_view_new ();

	renderer = gtk_cell_renderer_text_new ();

/* MODIFY IT: column attributes */
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
												-1,
												"名称",
												renderer,
												"text", COL_NAME,
												NULL);

	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
												-1,
												"类型",
												renderer,
												"text", COL_TYPE,
												NULL);

	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
												-1,
												"数据",
												renderer,
												"text", COL_DATA,
												NULL);
/* END OF column attributes */


/* MODIFY IT: column data types */
	store = gtk_list_store_new (COL_LIST_VIEW, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

	gtk_tree_view_set_model (GTK_TREE_VIEW (view), GTK_TREE_MODEL (store));

	g_object_unref (store);

	return view;
}

/* MODIFY IT: columns */
void liststore_insert (GtkTreeView *treeview, const char *name, const char *type, const char *data) { 

	GtkListStore *store;
	GtkTreeIter iter;
	
	store = GTK_LIST_STORE (gtk_tree_view_get_model (treeview));

/* MODIFY IT: columns */	
	gtk_list_store_append (store, &iter);
	gtk_list_store_set (store, &iter,
			COL_NAME, name,
			COL_TYPE, type,
			COL_DATA, data,
			-1);
}


