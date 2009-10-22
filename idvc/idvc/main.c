#include <gtk/gtk.h>
#include "idvc.h"
#include "idvc_list.h"
#include "idvc_menu.h"
#include "idvc_toolbar.h"

static void init_gui (Idvc *idvc_data);

int main (int argc, char *argv[])
{
	Idvc *idvc_data;

	gtk_init (&argc, &argv);

	idvc_data = idvc_new ();

	init_gui (idvc_data);

	gtk_widget_show_all (idvc_get_window (idvc_data));

	gtk_main();

	idvc_free (idvc_data);

	return 0;
}

#define IDVC_SPACING 2
#define IDVC_PADDING 0
static void init_gui (Idvc *idvc_data)
{
	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *menubar;
	GtkWidget *toolbar;
	GtkWidget *hpaned;
	GtkWidget *list;
	GtkWidget *notebook;
	GtkWidget *statusbar;

	GtkWidget *sw_idv1;
	GtkWidget *sw_idv2;
	GtkWidget *label;

/* window */
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "IDV Converter");
	gtk_window_set_default_size (GTK_WINDOW (window), 600, 400);
	g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit), NULL);
	idvc_set_window (idvc_data, window);

/* vbox */
	vbox = gtk_vbox_new (FALSE, IDVC_SPACING);
	gtk_container_add (GTK_CONTAINER (window), vbox);

/* menu */
	menubar = idvc_menu_new (idvc_data);
	gtk_box_pack_start (GTK_BOX(vbox), menubar, FALSE, FALSE, IDVC_PADDING);

/* toolbar */
	toolbar = idvc_toolbar_new (idvc_data);
	gtk_box_pack_start (GTK_BOX (vbox), toolbar, FALSE, FALSE, IDVC_PADDING);

/* hpaned */
	hpaned = gtk_hpaned_new ();
	gtk_paned_set_position (GTK_PANED (hpaned), 400);
	gtk_box_pack_start (GTK_BOX (vbox), hpaned, TRUE, TRUE, IDVC_PADDING);

/* list */
	list = idvc_list_new (idvc_data);
	gtk_paned_add1 (GTK_PANED (hpaned), list);
	idvc_set_list (idvc_data, list);

/* notebook */
	notebook = gtk_notebook_new ();
	gtk_paned_add2 (GTK_PANED (hpaned), notebook);

	sw_idv1 = gtk_scrolled_window_new (NULL, NULL);
	label = gtk_label_new ("IDV1");
	gtk_notebook_append_page (GTK_NOTEBOOK (notebook), sw_idv1, label);

	sw_idv2 = gtk_scrolled_window_new (NULL, NULL);
	label = gtk_label_new ("IDV2");
	gtk_notebook_append_page (GTK_NOTEBOOK (notebook), sw_idv2, label);

/* statusbar */
	statusbar = gtk_statusbar_new ();
	gtk_box_pack_start (GTK_BOX (vbox), statusbar, FALSE, FALSE, IDVC_PADDING);
	idvc_set_statusbar (idvc_data, statusbar);
}
