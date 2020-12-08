#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include "option.h"
#include "icmp.h"
#include "handler.h"

typedef struct {
	GtkWidget *window;
	GtkWidget *site;
	GtkWidget *buff;
	GtkWidget *time;
	GtkWidget *max;
	Icmp *icmp;
} Option;

static const char *get_entry (GtkEntry *entry) {
	const char *string = NULL;
	string = gtk_entry_get_text (entry);
	
	if (strcmp (string, "") == 0)
		return NULL;
	else
		return string;
		
}

static gboolean on_delete_event (GtkWidget *widget, GdkEvent *event, Option *option) {
	gtk_widget_destroy (GTK_WIDGET (option->window));
	g_slice_free (Option, option);

	return FALSE;
}

static void on_cancel_clicked (GtkButton *button, Option *option) {
	gtk_widget_destroy (GTK_WIDGET (option->window));
	g_slice_free (Option, option);
}

static void on_ok_clicked (GtkButton *button, Option *option) {

	const char *site;
	const char *buff;
	const char *time;
	const char *max;


	site = get_entry (GTK_ENTRY (option->site));
	buff = get_entry (GTK_ENTRY (option->buff));
	time = get_entry (GTK_ENTRY (option->time));
	max = get_entry (GTK_ENTRY (option->max));

	if (site == NULL || buff == NULL || time == NULL || max == NULL) {
		error_message ("不完整的输入");
		return;
	}


	
	strcpy (option->icmp->hostname, site);
	gtk_entry_set_text (GTK_ENTRY (option->icmp->entry), site);
	option->icmp->size = atoi (buff);
	option->icmp->time = atoi (time);
	option->icmp->num = atoi (max);

	gtk_widget_destroy (GTK_WIDGET (option->window));

	g_slice_free (Option, option);

}

void on_option_clicked (GtkButton *button, gpointer data) {

	Icmp *icmp = (Icmp *) data;

	char str[100];
	str[0] = '\0';

	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *hbox;
	GtkWidget *site;
	GtkWidget *buff;
	GtkWidget *time;
	GtkWidget *max;
	GtkWidget *ok;
	GtkWidget *cancel;
	GtkWidget *label;

	Option *option;
	option = g_slice_new (Option);
	if (option == NULL) {
		fprintf (stderr, "Error: not enough space\n");
		exit (1);
	}

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "Ping选项设置");
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);

	vbox = gtk_vbox_new (FALSE, 5);
	gtk_container_add (GTK_CONTAINER (window), vbox);

//
	hbox = gtk_hbox_new (FALSE, 2);
	gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 2);

	label = gtk_label_new ("默认站点：");
	gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, FALSE, 2);

	site = gtk_entry_new ();
	gtk_entry_set_text (GTK_ENTRY (site), DEFAULT_HOSTNAME);
	gtk_box_pack_start (GTK_BOX (hbox), site, FALSE, FALSE, 2);
	

//
	hbox = gtk_hbox_new (FALSE, 2);
	gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 2);

	label = gtk_label_new ("Ping Buffer Size:");
	gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, FALSE, 2);

	buff = gtk_entry_new ();
	sprintf (str, "%d", icmp->size);
	gtk_entry_set_text (GTK_ENTRY (buff), str);
	gtk_box_pack_start (GTK_BOX (hbox), buff, FALSE, FALSE, 2);

	label = gtk_label_new ("bytes");
	gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, FALSE, 2);

//
	hbox = gtk_hbox_new (FALSE, 2);
	gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 2);

	label = gtk_label_new ("Ping Timeout:");
	gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, FALSE, 2);

	time = gtk_entry_new ();
	sprintf (str, "%d", icmp->time);
	gtk_entry_set_text (GTK_ENTRY (time), str);
	gtk_box_pack_start (GTK_BOX (hbox), time, FALSE, FALSE, 2);

	label = gtk_label_new ("mSec");
	gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, FALSE, 2);

//
	hbox = gtk_hbox_new (FALSE, 2);
	gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 2);

	label = gtk_label_new ("Max Hops");
	gtk_box_pack_start (GTK_BOX (hbox), label, FALSE, FALSE, 2);

	max = gtk_entry_new ();
	sprintf (str, "%d", icmp->num);
	gtk_entry_set_text (GTK_ENTRY (max), str);
	gtk_box_pack_start (GTK_BOX (hbox), max, FALSE, FALSE, 2);

//
	hbox = gtk_hbox_new (FALSE, 2);
	gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 2);

	ok = gtk_button_new_with_label ("确定");
	gtk_box_pack_start (GTK_BOX (hbox), ok, FALSE, FALSE, 2);

	cancel = gtk_button_new_with_label ("取消");
	gtk_box_pack_end (GTK_BOX (hbox), cancel, FALSE, FALSE, 2);

//
	option->icmp = icmp;
	option->window = window;
	option->site = site;
	option->buff = buff;
	option->time = time;
	option->max = max;
//	

	g_signal_connect (G_OBJECT (window), "delete-event", G_CALLBACK (on_delete_event), option);

	g_signal_connect (GTK_BUTTON (cancel), "clicked", G_CALLBACK (on_cancel_clicked), option);

	g_signal_connect (GTK_BUTTON (ok), "clicked", G_CALLBACK (on_ok_clicked), option);

	gtk_widget_show_all (window);

}
