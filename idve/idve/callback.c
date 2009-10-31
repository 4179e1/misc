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
		GSList *ptr = pathlist;
		while (ptr != NULL)
		{
			idve_liststore_insert (idve, (gchar *)ptr->data);
			g_free (ptr->data);
			ptr = g_slist_next (ptr);
		}
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

/* Private func */
static GSList *get_path (GtkWindow *parent, GtkFileChooserAction action)
{
	GtkWidget *chooser;
	GtkFileFilter *filter;
	GSList *pathlist = NULL;

	chooser = gtk_file_chooser_dialog_new ("Select...",
			parent,
			action,
			GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, /* button, response_id */
			GTK_STOCK_OK, GTK_RESPONSE_OK,
			NULL);
	gtk_file_chooser_set_select_multiple (GTK_FILE_CHOOSER (chooser), TRUE);
	
/* add a filter, we only handle mp3 files */	
	filter = gtk_file_filter_new ();
	gtk_file_filter_set_name (filter, "mp3 Files");
	gtk_file_filter_add_pattern (filter, "*.mp3");
	gtk_file_chooser_add_filter (GTK_FILE_CHOOSER (chooser), filter);

	if (gtk_dialog_run (GTK_DIALOG (chooser)) == GTK_RESPONSE_OK)
	{
		pathlist = gtk_file_chooser_get_filenames (GTK_FILE_CHOOSER (chooser));
	}

	gtk_widget_destroy (chooser);
	return pathlist;
}
