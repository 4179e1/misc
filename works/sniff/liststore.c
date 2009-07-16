#include <gtk/gtk.h>
#include "liststore.h"

/* MODIFY IT: columns */
enum
{
	COL_PROTOCOL = 0,
	COL_SIP,
	COL_SPORT,
	COL_DIP,
	COL_DPORT,
	COL_SIZE,
	COL_PDATA,
	NUM_COLS
};

/* MODIFY IT: columns */
void liststore_insert (GtkTreeView *treeview, const char *protocol, const char *sip, const int sport, const char *dip, const int dport, const int size, const char *pdata) { 

	GtkListStore *store;
	GtkTreeIter iter;
	
	store = GTK_LIST_STORE (gtk_tree_view_get_model (treeview));

/* MODIFY IT: columns */	
	gtk_list_store_prepend (store, &iter);
	gtk_list_store_set (store, &iter,
			COL_PROTOCOL, protocol,
			COL_SIP, sip,
			COL_SPORT, sport,
			COL_DIP, dip,
			COL_DPORT, dport,
			COL_SIZE, size,
			COL_PDATA,  g_convert (pdata, -1, "UTF-8", "GBK", NULL, NULL, NULL),
			-1);
}

GtkWidget* create_view_and_model (void) {
	GtkCellRenderer *renderer;
	GtkListStore *store;
	GtkWidget *view;

	view = gtk_tree_view_new ();

	renderer = gtk_cell_renderer_text_new ();

/* MODIFY IT: column attributes */
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
												-1,
												"协议",
												renderer,
												"text", COL_PROTOCOL,
												NULL);

	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
												-1,
												"源地址",
												renderer,
												"text", COL_SIP,
												NULL);

	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
												-1,
												"端口",
												renderer,
												"text", COL_SPORT,
												NULL);

	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
												-1,
												"目的地址",
												renderer,
												"text", COL_DIP,
												NULL);

	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
												-1,
												"端口",
												renderer,
												"text", COL_DPORT,
												NULL);
	
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
												-1,
												"大小",
												renderer,
												"text", COL_SIZE,
												NULL);

	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
												-1,
												"数据",
												renderer,
												"text", COL_PDATA,
												NULL);
/* END OF column attributes */


/* MODIFY IT: column data types */
	store = gtk_list_store_new (NUM_COLS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING);

	gtk_tree_view_set_model (GTK_TREE_VIEW (view), GTK_TREE_MODEL (store));

	g_object_unref (store);

	return view;
}

void remove_tree_view(GtkTreeView *tree)
{
	GtkListStore *store;
	GtkTreeModel *model;
	GtkTreeIter iter;
	
	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(tree)));
	model = gtk_tree_view_get_model(GTK_TREE_VIEW(tree));
	
	if (gtk_tree_model_get_iter_first(model, &iter) == FALSE)
		return;

	gtk_list_store_clear(store);
}
