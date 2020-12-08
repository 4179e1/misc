#include <gtk/gtk.h>

int main (int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *entry;

	gtk_init (&argc, &argv);


	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

	vbox = gtk_vbox_new (FALSE, 2);
	gtk_container_add (GTK_CONTAINER (window), vbox);


	entry = gtk_entry_new_with_max_length (8);
	gtk_box_pack_start_defaults (GTK_BOX (vbox), entry);


	gtk_entry_set_text (GTK_ENTRY (entry), "1234567890");

	gtk_widget_show_all (window);

	gtk_main();

	return 0;
}
