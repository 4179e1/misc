#include <gtk/gtk.h>

void on_bt_show_title_clicked(GtkWidget *widget, gpointer window)
{
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) {
		gtk_window_set_title(window, "Title");
	} else {
		gtk_window_set_title(window, "");
	}
}

int main(int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *fixed;
	GtkWidget *bt_quit;
	GtkWidget *bt_show_title;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
	gtk_window_set_title(GTK_WINDOW(window), "Title");

	fixed = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window), fixed);

	bt_quit = gtk_button_new_with_label("Quit");
	gtk_widget_set_size_request(bt_quit, 80, 35);
	gtk_fixed_put(GTK_FIXED(fixed), bt_quit, 20, 20);

	bt_show_title = gtk_check_button_new_with_label("Show title");
	gtk_widget_set_size_request(bt_show_title, 80, 35);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(bt_show_title), TRUE);
//	GTK_WIDGET_UNSET_FLAGS(bt_show_title, GTK_CAN_FOCUS);
	gtk_fixed_put(GTK_FIXED(fixed), bt_show_title, 20, 80);

	g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), G_OBJECT(window));

	g_signal_connect(G_OBJECT(bt_quit), "clicked", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(bt_show_title), "clicked", G_CALLBACK(on_bt_show_title_clicked), (gpointer) window);

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}
