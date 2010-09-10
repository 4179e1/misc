#include <gtk/gtk.h>
#include "myipaddress.h"

void on_button_clicked (GtkButton *button, MyIPAddress *ma)
{
	gchar *msg = my_ip_address_get_address (ma);
	if (msg != NULL)
	{
		g_print ("%s\n", msg);
	}
}

int main(int argc, char* argv[])
{
	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *ip_entry;
	GtkWidget *button;
	
	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

	vbox = gtk_vbox_new(FALSE, 2);
	gtk_container_add (GTK_CONTAINER (window), vbox);

	ip_entry = my_ip_address_new ();
	gtk_box_pack_start_defaults (GTK_BOX (vbox), ip_entry);

	button = gtk_button_new_with_label ("Get IP");
	gtk_box_pack_start_defaults (GTK_BOX (vbox), button);

	g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (on_button_clicked), ip_entry);

	gtk_widget_show_all (window);

	gtk_main();
	
	return 0;
}
