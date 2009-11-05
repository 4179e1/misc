#include <gtk/gtk.h>
#include "idve.h"
#include "callback.h"

#include <sys/stat.h>
#include <string.h>

/* the same as linux */
#define IDVE_PATH_LEN 4096

static GSList *get_path (GtkWindow *parent, GtkFileChooserAction action);
static void listfile (Idve *idve, char* path);
static gpointer open_thread (Idve *idve);


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
void on_liststore_delete (gpointer *widget, Idve *idve)
{
	GtkTreeSelection *selection;
	GList *list;
	GList *ref_list = NULL;
	GList *ptr;
	GtkTreeRowReference *ref;
	GtkTreeModel *model;


	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (idve_get_list (idve)));
	
	list = gtk_tree_selection_get_selected_rows (selection, 
			(GtkTreeModel **)idve_get_liststore_ref (idve));

	/* convert GtkTreePath to GtkTreeRowReference */
	model = GTK_TREE_MODEL (idve_get_liststore (idve));
	for (ptr = list; ptr != NULL; ptr = g_list_next (ptr))
	{
		ref = gtk_tree_row_reference_new (model, (GtkTreePath *)ptr->data);
		ref_list = g_list_prepend (ref_list, ref);
		gtk_tree_path_free (ptr->data);
	}

	for (ptr = ref_list; ptr != NULL; ptr = g_list_next (ptr))
	{
		GtkTreePath *path;
		path = gtk_tree_row_reference_get_path ((GtkTreeRowReference *)ptr->data);

		if (path)
		{
			GtkTreeIter iter;

			if (gtk_tree_model_get_iter (model, &iter, path))
			{
				gtk_list_store_remove (GTK_LIST_STORE (model), &iter);
			}
		}
		gtk_tree_row_reference_free (ptr->data);
	}
	
	g_list_free (ref_list);
	g_list_free (list);
}


G_MODULE_EXPORT
void on_liststore_open (gpointer *widget, Idve *idve)
{
	GSList *pathlist;

	pathlist = get_path (GTK_WINDOW (idve_get_window (idve)),
			GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);

	if (pathlist != NULL)
	{
		if (idve_pointer_aquire (idve, (gpointer)pathlist))
		{
			GError *error = NULL;
			g_thread_create ((GThreadFunc)open_thread, idve, FALSE, &error);
			if (error != NULL)
			{
				g_warning ("%s", error->message);
				idve_pointer_release (idve);
				g_slist_foreach (pathlist, (GFunc)g_free, NULL);
				g_slist_free (pathlist);
			}
		}

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

/*
 * with glib, it works on both linux & windows,
 * but the path looks a bit strange on windows , it looks like:
 * 		"E:\code\idve\test/a.MP3"
 * windows use '\' as separator, but '/' still works.
*/
static void listfile (Idve *idve, gchar *path)
{
	GDir *dir;
	gchar *ptr;
	GError *error = NULL;
	const gchar *name;
	gint len;

	len = strlen (path);

	/* 
	 * test the path is a directory or not, 
	 * there's something worng with stat() family on window,
	 * we don't use it.
	 */
	if (!g_file_test (path, G_FILE_TEST_IS_DIR))
	{
		/* check the suffix, we only handle mp3 files, not case sensitive */
		if ((len >= 4) && (g_ascii_strcasecmp (&path[len - 4], ".mp3") == 0))
		{
			/* lock gobal variable */
			gdk_threads_enter ();
			idve_liststore_insert (idve, path);
			gdk_threads_leave ();

			/* add a sleep to test thread */
//			g_message ("about to sleep 1 second for testing");
//			g_usleep (1000000);
		}
		return;
	}

	ptr = path + len;
	*ptr++ = '/';
	*ptr = 0;

	dir = g_dir_open (path, 0, &error);
	if (error != NULL)
	{
		g_warning ("g_dir_open error");
		g_warning ("%s\n", error->message);
		g_free (error);
		return;
	}

	while ((name = g_dir_read_name (dir)) != NULL)
	{
		strcpy (ptr, name);
		listfile (idve, path);
	}

	ptr[-1] = 0;
	
	g_dir_close (dir);
}

static gpointer open_thread (Idve *idve)
{
	GSList *pathlist;
	GSList *ptr;
	gchar *path;

	pathlist = (GSList *)idve_get_pointer (idve);
	idve_pointer_release (idve);

	path = g_new (gchar, IDVE_PATH_LEN);

	ptr = pathlist;
	while (ptr != NULL)
	{
		g_strlcpy (path, (gchar *)ptr->data, IDVE_PATH_LEN);
		listfile (idve, path);
		g_free (ptr->data);
		ptr = g_slist_next (ptr);
	}
	g_slist_free (pathlist);

	g_free (path);
	return (gpointer)0;
}
