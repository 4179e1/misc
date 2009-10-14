#include <gtk/gtk.h>
#include "idvc.h"

static void gui_init (Idvc *idvc_info);

int main (int argc, char *argv[])
{
	Idvc *idvc_info;

	gtk_init (&argc, &argv);

	idvc_info = idvc_new ();

	gui_init (idvc_info);

	gtk_widget_show_all (idvc_get_window (idvc_info));

	gtk_main();

	idvc_free (idvc_info);

	return 0;
}

static void gui_init (Idvc *idvc_info)
{
	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *hpaned;
	GtkWidget *list;
	GtkWidget *statusbar;

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "IDV Converter");
	g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit), NULL);
	idvc_set_window (idvc_info, window);

}
