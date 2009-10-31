#include <gtk/gtk.h>
#include "idve.h"
#include "callback.h"

static GSList *get_path (GtkWindow *parent, GtkFileChooserAction action);

G_MODULE_EXPORT 
void on_liststore_insert (gpointer *widget, Idve *idve)
{
	GSList *pathlist;

	pathlist = get_path (GTK_WINDOW (idve_get_window (idve)),
			GTK_FILE_CHOOSER_ACTION_OPEN);
	
	if (pathlist != NULL)
	{
	//	idve_liststore_insert (idve, path);
	//	g_free (path);
		g_slist_free (pathlist);
	}
}


G_MODULE_EXPORT 
void on_liststore_clear (gpointer *widget, Idve *idve)
{
	idve_liststore_clear (idve);
}


G_MODULE_EXPORT 
void on_sidebar_toggle (gpointer *widget, Idve *idve)
{
	idve_sidebar_toggle (idve);
}

G_MODULE_EXPORT 
void on_statusbar_toggle (gpointer *widget, Idve *idve)
{
	idve_statusbar_toggle (idve);
}

static GSList *get_path (GtkWindow *parent, GtkFileChooserAction action)
{
	GtkWidget *chooser;
//	gchar *path = NULL;
	GSList *pathlist = NULL;

	chooser = gtk_file_chooser_dialog_new ("Select Path...",
			parent,
			action,
			GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, /* button_text, response_id */
			GTK_STOCK_OK, GTK_RESPONSE_OK,
			NULL);
	gtk_file_chooser_set_select_multiple (GTK_FILE_CHOOSER (chooser), TRUE);

	if (gtk_dialog_run (GTK_DIALOG (chooser)) == GTK_RESPONSE_OK)
	{
		pathlist = gtk_file_chooser_get_filenames (GTK_FILE_CHOOSER (chooser));
	}

	gtk_widget_destroy (chooser);
	return pathlist;
}
