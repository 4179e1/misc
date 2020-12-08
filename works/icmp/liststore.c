#include <gtk/gtk.h>

/* MODIFY IT: columns */
enum
{
	COL_ID = 0,
	COL_TIME,
	COL_IP,
	COL_MSG,
	NUM_COLS
};

/* MODIFY IT: columns */
void liststore_insert (GtkTreeView *treeview, const int id, const int time, const char *ip, const char *msg) { 

	GtkListStore *store;
	GtkTreeIter iter;
	
	store = GTK_LIST_STORE (gtk_tree_view_get_model (treeview));

/* MODIFY IT: columns */	
	gtk_list_store_append (store, &iter);
	gtk_list_store_set (store, &iter,
			COL_ID, id,
			COL_TIME, time,
			COL_IP, ip,
			COL_MSG, msg,
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
												"序号",
												renderer,
												"text", COL_ID,
												NULL);

	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
												-1,
												"时间",
												renderer,
												"text", COL_TIME,
												NULL);

	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
												-1,
												"IP地址",
												renderer,
												"text", COL_IP,
												NULL);

	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
												-1,
												"信息",
												renderer,
												"text", COL_MSG,
												NULL);
/* END OF column attributes */


/* MODIFY IT: column data types */
	store = gtk_list_store_new (NUM_COLS, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING);

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
