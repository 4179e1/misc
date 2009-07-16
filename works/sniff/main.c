#include <gtk/gtk.h>
#include <stdlib.h>
#include "sniff.h"
#include "liststore.h"
#include "check.h"

int main (int argc, char *argv[]) {
	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *sw;
	GtkWidget *treeview;
	GtkWidget *hbox;
	GtkWidget *check;
	GtkWidget *ok;
	GtkWidget *clear;

	Sniff *sniff;
	sniff = g_slice_new (Sniff);
	if (sniff == NULL) {
		fprintf (stderr, "Error: not enough space\n");
		exit (-1);
	}

	Queue queue;
	queue = CreateQueue (1024);

	gtk_init(&argc, &argv);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "网络嗅探器");
	gtk_window_set_default_size (GTK_WINDOW (window), 600, 400);
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);

	vbox = gtk_vbox_new (FALSE, 5);
	gtk_container_add (GTK_CONTAINER (window), vbox);

//
	sw = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (sw), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_box_pack_start (GTK_BOX (vbox), sw, TRUE, TRUE, 2);

	treeview = create_view_and_model();
	gtk_container_add (GTK_CONTAINER (sw), treeview);

//
	hbox = gtk_hbox_new (FALSE, 2);
	gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 2);

	check = gtk_button_new_with_label ("查看");
	gtk_widget_set_size_request (GTK_WIDGET (check), 60, -1);
	gtk_box_pack_start (GTK_BOX (hbox), check, FALSE, FALSE, 2);

	clear = gtk_button_new_with_label ("清除");
	gtk_widget_set_size_request (GTK_WIDGET (clear), 60, -1);
	gtk_box_pack_start (GTK_BOX (hbox), clear, FALSE, FALSE, 2);

	ok = gtk_button_new_with_label ("确定");
	gtk_widget_set_size_request (GTK_WIDGET (ok), 60, -1);
	gtk_box_pack_end (GTK_BOX (hbox), ok, FALSE, FALSE, 2);

//
	sniff->status = 0;
	sniff->button = check;
	sniff->treeview = treeview;
	sniff->queue = queue;
//	
	g_signal_connect_swapped (G_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit), G_OBJECT (window));

	g_signal_connect (GTK_BUTTON (check), "clicked", G_CALLBACK (on_check_clicked), (gpointer) sniff);
	g_signal_connect_swapped (GTK_BUTTON (clear), "clicked", G_CALLBACK (remove_tree_view), GTK_TREE_VIEW (treeview));
	g_signal_connect (GTK_BUTTON (ok), "clicked", G_CALLBACK (gtk_main_quit), (gpointer) sniff);

//	
	gtk_widget_show_all (window);

	gtk_main();

	g_slice_free (Sniff, sniff);

	DisposeQueue (queue);

	return 0;

}
