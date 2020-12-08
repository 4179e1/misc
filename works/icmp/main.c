#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include "icmp.h"
#include "liststore.h"
#include "ping.h"
#include "trace.h"
#include "option.h"
#include "stop.h"

int main (int argc, char *argv[]) {
	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *hbox;
	GtkWidget *box;
	GtkWidget *label;
	GtkWidget *entry;
	GtkWidget *name;
	GtkWidget *ns;
	GtkWidget *sw;
	GtkWidget *treeview;
	GtkWidget *frame;
	GtkWidget *table;
	GtkWidget *ping;
	GtkWidget *trace;
	GtkWidget *option;
	GtkWidget *clear;
	GtkWidget *stop;
	GtkWidget *quit;

	Icmp *icmp = g_slice_new (Icmp);
	if (icmp == NULL) {
		fprintf (stderr, "Error: not enough space\n");
		exit (0);
	}
	
	strcpy (icmp->hostname, DEFAULT_HOSTNAME);

	gtk_init (&argc, &argv);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size (GTK_WINDOW (window), 600, 400);
	gtk_window_set_title (GTK_WINDOW (window), "ICMP协议应用");
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);

	vbox = gtk_vbox_new (FALSE, 5);
	gtk_container_add (GTK_CONTAINER (window), vbox);

//	
	hbox = gtk_hbox_new (FALSE, 2);
	gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 2);

	label = gtk_label_new ("目标机器");
	gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, FALSE, 2);

	entry = gtk_entry_new ();
	gtk_entry_set_text (GTK_ENTRY (entry), icmp->hostname);
	gtk_box_pack_start (GTK_BOX (hbox), entry, FALSE, FALSE, 2);

	label = gtk_label_new ("机器名:");
	gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, FALSE, 2);

	name = gtk_label_new ("");
	gtk_box_pack_start (GTK_BOX (hbox), name, FALSE, FALSE, 2);

//
	hbox = gtk_hbox_new (FALSE, 5);
	gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 2);

	label = gtk_label_new ("显示结果:                     ");
	gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, FALSE, 2);

	label = gtk_label_new ("Name Server:");
	gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, FALSE, 2);

	ns = gtk_label_new ("");
	gtk_box_pack_start (GTK_BOX (hbox), ns, FALSE, FALSE, 2);

//
	sw = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (sw), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_box_pack_start (GTK_BOX (vbox), sw, TRUE, TRUE, 2);

	treeview = create_view_and_model ();
//	liststore_insert (GTK_TREE_VIEW (treeview), 1, "11:00", "192.168.1.1", "msg");
	gtk_container_add (GTK_CONTAINER (sw), treeview);

//
	hbox = gtk_hbox_new (FALSE, 5);
	gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 2);

	frame = gtk_frame_new ("静态");
	gtk_box_pack_start (GTK_BOX (hbox), frame, FALSE, FALSE, 2);

	table = gtk_table_new (2, 2, TRUE);
//	gtk_table_set_col_spacings (GTK_TABLE (table), 5);
//	gtk_table_set_row_spacings (GTK_TABLE (table), 5);
	gtk_container_add (GTK_CONTAINER (frame), table);

	ping = gtk_button_new_with_label ("Ping");
	trace = gtk_button_new_with_label ("Trace Route");
	option = gtk_button_new_with_label ("选项");
	clear = gtk_button_new_with_label ("清除列表");
	gtk_table_attach (GTK_TABLE (table), ping, 0, 1, 0, 1, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 5, 5);
	gtk_table_attach (GTK_TABLE (table), trace, 1, 2, 0, 1, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 5, 5);
	gtk_table_attach (GTK_TABLE (table), option, 0, 1, 1, 2, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 5, 5);
	gtk_table_attach (GTK_TABLE (table), clear, 1, 2, 1, 2, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 5, 5);

	box = gtk_vbox_new (TRUE, 5);
	gtk_box_pack_end (GTK_BOX (hbox), box, FALSE, FALSE, 2);

	stop = gtk_button_new_with_label ("停止");
	gtk_widget_set_size_request (GTK_WIDGET (stop), 60, -1);
	gtk_box_pack_start (GTK_BOX (box), stop, TRUE, FALSE, 2);

	quit = gtk_button_new_with_label ("退出");
	gtk_box_pack_start (GTK_BOX (box), quit, TRUE, FALSE, 2);

//
	icmp->treeview = treeview;
	icmp->entry = entry;
	icmp->time = atoi (DEFAULT_TIME);
	icmp->num = atoi (DEFAULT_NUM);
	icmp->size = atoi (DEFAULT_BUFF);
	icmp->ping = ping;
	icmp->trace = trace;
	icmp->status = 0;

//
	g_signal_connect_swapped (G_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit), G_OBJECT (window));

	g_signal_connect (GTK_BUTTON (ping), "clicked", G_CALLBACK (on_ping_clicked), icmp);
	g_signal_connect (GTK_BUTTON (trace), "clicked", G_CALLBACK (on_trace_clicked), icmp);
	g_signal_connect (GTK_BUTTON (option), "clicked", G_CALLBACK (on_option_clicked), icmp);
	g_signal_connect (GTK_BUTTON (stop), "clicked", G_CALLBACK (on_stop_clicked), icmp);
	g_signal_connect_swapped (GTK_BUTTON (clear), "clicked", G_CALLBACK (remove_tree_view), GTK_TREE_VIEW (treeview));

	g_signal_connect_swapped (G_OBJECT (quit), "clicked", G_CALLBACK (gtk_main_quit), G_OBJECT (window));
	
	gtk_widget_show_all (window);

	gtk_main();

	g_slice_free (Icmp, icmp);

	return 0;
}

