#include <gtk/gtk.h>

/* MODIFY IT: columns */
enum
{
	COL_NAME = 0,
	COL_AGE,
	NUM_COLS
};

/* MODIFY IT: columns */
static void liststore_insert (GtkTreeView *treeview, char const *name, const int age) { 

	GtkListStore *store;
	GtkTreeIter iter;
	
	store = GTK_LIST_STORE (gtk_tree_view_get_model (treeview));

/* MODIFY IT: columns */	
	gtk_list_store_append (store, &iter);
	gtk_list_store_set (store, &iter,
			COL_NAME, name,
			COL_AGE, age,
			-1);
}

static GtkWidget* create_view_and_model (void) {
	GtkCellRenderer *renderer;
	GtkListStore *store;
	GtkWidget *view;

	view = gtk_tree_view_new ();

	renderer = gtk_cell_renderer_text_new ();

/* MODIFY IT: column attributes */
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
												-1,
												"Name",
												renderer,
												"text", COL_NAME,
												NULL);

	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
												-1,
												"Age",
												renderer,
												"text", COL_AGE,
												NULL);
/* END OF column attributes */


/* MODIFY IT: column data types */
	store = gtk_list_store_new (NUM_COLS, G_TYPE_STRING, G_TYPE_INT);

	gtk_tree_view_set_model (GTK_TREE_VIEW (view), GTK_TREE_MODEL (store));

	g_object_unref (store);

	return view;
}

static void onTreeViewRowActivated (GtkTreeView *view, GtkTreePath *path, GtkTreeViewColumn *col, gpointer userdata) {
	GtkTreeIter iter;
	GtkTreeModel *model;

	model = gtk_tree_view_get_model (view);

	if (gtk_tree_model_get_iter (model, &iter, path))
	{
		gchar *name;

		gtk_tree_model_get (model, &iter, COL_NAME, &name, -1);

		g_print ("The row containing the name '%s' has been double-clicked.\n", name);

		g_free (name);
	}
}

int main (int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *view;

	gtk_init (&argc, &argv);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	
	view = create_view_and_model ();
	gtk_tree_view_set_headers_clickable (GTK_TREE_VIEW (view), TRUE);
	gtk_container_add (GTK_CONTAINER (window), view);

	liststore_insert (GTK_TREE_VIEW (view), "orz", 11);
	liststore_insert (GTK_TREE_VIEW (view), "oho", 12);

	g_signal_connect_swapped (G_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit), G_OBJECT (window));
	
	g_signal_connect (GTK_TREE_VIEW (view), "row-activated", G_CALLBACK (onTreeViewRowActivated), NULL);

	gtk_widget_show_all (window);

	gtk_main ();

	return 0;

}

