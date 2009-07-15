#include <gtk/gtk.h>

void show_info(GtkButton *button, gpointer aboutdialog)
{
	gtk_dialog_run(GTK_DIALOG(aboutdialog));
	gtk_widget_hide(aboutdialog);

}


int main(int argc, char* argv[])
{
	GtkBuilder *builder;
	GtkWidget *window;
	GtkWidget *aboutdialog;
	GtkWidget *info;

	gtk_init(&argc, &argv);

	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "dialog.xml", NULL);
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
	aboutdialog = GTK_WIDGET(gtk_builder_get_object(builder, "aboutdialog"));
//	info = GTK_WIDGET(gtk_builder_get_object(builder, "info"));
	gtk_builder_connect_signals(builder, NULL);

	g_object_unref(G_OBJECT(builder));

//	g_signal_connect_swapped(G_OBJECT(info), "clicked", G_CALLBACK(show_info), (gpointer)aboutdialog);


	gtk_widget_show(window);
	gtk_main();

	return 0;
}
