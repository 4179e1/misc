#include <gtk/gtk.h>
#include <stdlib.h>
#include "odbc.h"
#include "liststore.h"
#include "sql.h"

int main (int argc, char *argv[]) {
	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *hbox;
	GtkWidget *sw;
	GtkWidget *treeview;
	GtkWidget *label;
	GtkWidget *entry;
	GtkWidget *button;

	Data *data;
	data = g_slice_new (Data);
	if (data == NULL) {
		fprintf (stderr, "Error: not enough space\n");
		exit (-1);
	}

	gtk_init (&argc, &argv);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "ODBC");
	gtk_window_set_default_size (GTK_WINDOW (window), 600, 400);
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);

	vbox = gtk_vbox_new (FALSE, 5);
	gtk_container_add (GTK_CONTAINER (window), vbox);

	sw = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (sw), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_box_pack_start (GTK_BOX (vbox), sw, TRUE, TRUE, 0);

	treeview = create_view_and_model ();
	gtk_container_add (GTK_CONTAINER (sw), treeview);

	hbox = gtk_hbox_new (FALSE, 5);
	gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);
	
	label = gtk_label_new ("WebSite: ");
	gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, FALSE, 0);

	entry = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX (hbox), entry, TRUE, TRUE, 0);

	button = gtk_button_new_with_label ("查询");
	gtk_box_pack_start (GTK_BOX (hbox), button, FALSE, FALSE, 0);

	data->treeview = treeview;
	data->entry = entry;

	g_signal_connect_swapped (G_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit), G_OBJECT (window));
	g_signal_connect (GTK_BUTTON (button), "clicked", G_CALLBACK (on_button_clicked), data);

	gtk_widget_show_all (window);

	gtk_main();

	g_slice_free (Data, data);

	return 0;
}
