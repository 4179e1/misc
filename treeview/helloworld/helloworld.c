#include <gtk/gtk.h>

enum
{
	COL_NAME = 0,
	COL_AGE,
	NUM_COLS
};

void onTreeViewRowActivated (GtkTreeView *view, GtkTreePath *path, GtkTreeViewColumn *col, gpointer userdata) {
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

static GtkTreeModel * create_and_fill_model (voie) {
	GtkListStore *store;
	GtkTreeIter iter;

	store = gtk_list_store_new (NUM_COLS, G_TYPE_STRING, G_TYPE_UINT);

	gtk_list_store_append (store, &iter);
	gtk_list_store_set (store, &iter,
			COL_NAME, "Heinz El-Mann",
			COL_AGE, 51,
			-1);

	gtk_list_store_append (store, &iter);
	gtk_list_store_set (store, &iter,
			COL_NAME, "Jane Doe",
			COL_AGE, 23,
			-1);

	gtk_list_store_append (store, &iter);
	gtk_list_store_set (store, &iter,
			COL_NAME, "Joe Bungop",
			COL_AGE, 91,
			-1);

	return GTK_TREE_MODEL (store);
}

static GtkWidget* create_view_and_model (void) {
	GtkCellRenderer *renderer;
	GtkTreeModel *model;
	GtkWidget *view;

	view = gtk_tree_view_new ();

	renderer = gtk_cell_renderer_text_new ();
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
	model = create_and_fill_model ();
	gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);

	g_object_unref (model);

	return view;
}

int main (int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *view;

	gtk_init (&argc, &argv);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	
	view = create_view_and_model ();
	gtk_container_add (GTK_CONTAINER (window), view);

	g_signal_connect_swapped (G_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit), G_OBJECT (window));
	
	g_signal_connect (GTK_TREE_VIEW (view), "row-activated", G_CALLBACK (onTreeViewRowActivated), NULL);

	gtk_widget_show_all (window);

	gtk_main ();

	return 0;

}

