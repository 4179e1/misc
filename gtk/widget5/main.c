#include <gtk/gtk.h>

int main(int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *table;

	GtkWidget *label1;
	GtkWidget *label2;
	GtkWidget *label3;

	GtkWidget *entry1;
	GtkWidget *entry2;
	GtkWidget *entry3;

	gtk_init(&argc, &argv);
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

	table = gtk_table_new(3, 2, FALSE);
	gtk_container_add(GTK_CONTAINER(window), table);

	label1 = gtk_label_new("Name");
	label2 = gtk_label_new("Age");
	label3 = gtk_label_new("Occupation");

	gtk_table_attach(GTK_TABLE(table), label1, 0, 1, 0, 1, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), label2, 0, 1, 1, 2, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), label3, 0, 1, 2, 3, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

	entry1 = gtk_entry_new();
	entry2 = gtk_entry_new();
	entry3 = gtk_entry_new();

	gtk_table_attach(GTK_TABLE(table), entry1, 1, 2, 0, 1, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), entry2, 1, 2, 1, 2, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE(table), entry3, 1, 2, 2, 3, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

	g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), G_OBJECT(window));

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}
