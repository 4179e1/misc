#include <gtk/gtk.h>

  enum
  {
    COL_ICON = 0,
    COL_TEXT,
    NUM_COLS
  };

  GtkListStore *
  create_liststore(void)
  {
    GtkListStore  *store;
    GtkTreeIter    iter;
    GdkPixbuf     *icon;
    GError        *error = NULL;

    store = gtk_list_store_new(2, GDK_TYPE_PIXBUF, G_TYPE_STRING);

    icon = gdk_pixbuf_new_from_file("icon.png", &error);
    if (error)
    {
      g_warning ("Could not load icon: %s\n", error->message);
      g_error_free(error);
      error = NULL;
    }

    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter,
                       COL_ICON, icon,
                       COL_TEXT, "example",
                       -1);

    return store;
  }

  GtkWidget *
  create_treeview(void)
  {
    GtkTreeModel      *model;
    GtkTreeViewColumn *col;
    GtkCellRenderer   *renderer;
    GtkWidget         *view;

    model = GTK_TREE_MODEL(create_liststore());

    view = gtk_tree_view_new_with_model(model);

    col = gtk_tree_view_column_new();
    gtk_tree_view_column_set_title(col, "Title");

    renderer = gtk_cell_renderer_pixbuf_new();
    gtk_tree_view_column_pack_start(col, renderer, FALSE);
    gtk_tree_view_column_set_attributes(col, renderer,
                                        "pixbuf", COL_ICON,
                                        NULL);

    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_column_pack_start(col, renderer, TRUE);
    gtk_tree_view_column_set_attributes(col, renderer,
                                        "text", COL_TEXT,
                                        NULL);

    gtk_tree_view_append_column(GTK_TREE_VIEW(view), col);

    gtk_widget_show_all(view);

    return view;
  }

int main (int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *view;

	gtk_init (&argc, &argv);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	
	view = create_treeview ();
	gtk_container_add (GTK_CONTAINER (window), view);

	g_signal_connect_swapped (G_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit), G_OBJECT (window));
	
	gtk_widget_show_all (window);

	gtk_main ();

	return 0;

}


