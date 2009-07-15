#include <gtk/gtk.h>

void show_info(GtkWidget *widget, gpointer window)
{
	GtkWidget *dialog;
	dialog = gtk_message_dialog_new(window,
			GTK_DIALOG_DESTROY_WITH_PARENT,
			GTK_MESSAGE_INFO,
			GTK_BUTTONS_OK,
			"Info",
			"title");
	gtk_window_set_title(GTK_WINDOW(window), "Info");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}

void show_about(GtkWidget *widget, gpointer window)
{	
	GdkPixbuf*pixbuf = gdk_pixbuf_new_from_file("battery.png", NULL);

	GtkWidget *dialog = gtk_about_dialog_new();
	gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(dialog), "Battery");
	gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), "0.9");
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog), "(c) lyre");
	gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog), "O 'Rly?");
	gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog), "www.orz.com");
	gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog), pixbuf);
	
	g_object_unref(pixbuf), pixbuf = NULL;

	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}

int main(int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *table;

	GtkWidget *info;
	GtkWidget *about;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(window), 220, 150);
	gtk_window_set_title(GTK_WINDOW(window), "Message dialogs");

	table = gtk_table_new(2, 2, TRUE);

	info = gtk_button_new_with_label("Info");
	about = gtk_button_new_with_label("About");

	gtk_table_attach(GTK_TABLE(table), info, 0, 1, 0, 1, GTK_FILL, GTK_FILL, 3, 3);
	gtk_table_attach(GTK_TABLE(table), about, 1, 2, 0, 1, GTK_FILL, GTK_FILL, 3, 3);

	gtk_container_add(GTK_CONTAINER(window), table);

	g_signal_connect(G_OBJECT(info), "clicked", G_CALLBACK(show_info), (gpointer) window);
	g_signal_connect(G_OBJECT(about), "clicked", G_CALLBACK(show_about), (gpointer) window);

	g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), (gpointer) window);

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}
