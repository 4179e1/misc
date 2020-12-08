#include <gtk/gtk.h>
#include <assert.h>

enum
{
	COL_DISPLAY_NAME,
	COL_PIXBUF,
	NUM_COLS,
};

GtkTreeModel *init_model(void)
{
	GtkListStore *list_store;
	GdkPixbuf *p1, *p2, *p3, *p4;
	GtkTreeIter iter;
	GError *err = NULL;

	p1 = gdk_pixbuf_new_from_file("icon/1.png", &err);
	p2 = gdk_pixbuf_new_from_file("icon/2.png", &err);
	p3 = gdk_pixbuf_new_from_file("icon/3.png", &err);
	p4 = gdk_pixbuf_new_from_file("icon/4.png", &err);

	assert(err==NULL);	
	/*The first argument NUM_COLS is the column number of list_store,
	  the rest are types of data*/
	list_store = gtk_list_store_new(NUM_COLS, G_TYPE_STRING, GDK_TYPE_PIXBUF);

	int i = 0;
	for (i; i < 1; i++) {
		gtk_list_store_append(list_store, &iter);	//Appends a new row to list_store. iter will be changed to point to this new row. The row will be empty after this function is called. To fill in values, you need to call gtk_list_store_set() or gtk_list_store_set_value().
		gtk_list_store_set(list_store, &iter, COL_DISPLAY_NAME, "p1", COL_PIXBUF, p1, -1);
		gtk_list_store_append(list_store, &iter);
		gtk_list_store_set(list_store, &iter, COL_DISPLAY_NAME, "p2", COL_PIXBUF, p2, -1);
		gtk_list_store_append(list_store, &iter);
		gtk_list_store_set(list_store, &iter, COL_DISPLAY_NAME, "p3", COL_PIXBUF, p3, -1);
		gtk_list_store_append(list_store, &iter);
		gtk_list_store_set(list_store, &iter, COL_DISPLAY_NAME, "p4", COL_PIXBUF, p4, -1);
	}

	return GTK_TREE_MODEL(list_store);
}

int main(int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *icon_view;
	GtkWidget *sw;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(window, 350, 330);

	sw = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(sw), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(sw), GTK_SHADOW_ETCHED_IN);
	gtk_container_add(GTK_CONTAINER(window), sw);

	icon_view = gtk_icon_view_new_with_model(init_model());
	gtk_icon_view_set_text_column(GTK_ICON_VIEW(icon_view), COL_DISPLAY_NAME);
	gtk_icon_view_set_pixbuf_column(GTK_ICON_VIEW(icon_view), COL_PIXBUF);
	gtk_icon_view_set_selection_mode(GTK_ICON_VIEW(icon_view), GTK_SELECTION_MULTIPLE);
	gtk_container_add(GTK_CONTAINER(sw), icon_view);

	g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}
