#include <gtk/gtk.h>
#include "id3e.h"
#include "callback.h"
#include "id3v1.h"
#include "gv1.h"

#include <string.h>

/* the same as linux */
#define ID3E_PATH_LEN 4096

static GSList *get_path (GtkWindow *parent, GtkFileChooserAction action);
static void listfile (Id3e *id3e, char* path);

G_MODULE_EXPORT
void on_selection_changed (GtkTreeSelection *selection, Id3e *id3e)
{
	GList *list;
	GList *ptr;
	GtkTreeModel *model;
	GtkTreeIter iter;
	gchar *path;
	gint selected_num;
	Id3v1 *tag = NULL;
	Gv1 *gv1;

	selected_num = gtk_tree_selection_count_selected_rows (selection);
	gv1 = id3e_get_gv1 (id3e);
	gv1_reset (gv1);
	id3e_statusbar_message (id3e, "Selected %d rows", selected_num);

	/* not thing selected */
	if (selected_num == 0)
	{
		/* TODO: reset gv1 */
		return;
	}

	/* ok, selected something, initial some variable */
	path = g_new (gchar, ID3E_PATH_LEN);
	model = GTK_TREE_MODEL (id3e_get_list_store (id3e));
	list = gtk_tree_selection_get_selected_rows (selection,
			&model);
	ptr = list;

	/* only 1 row selected */
	if (selected_num == 1)
	{
		if (gtk_tree_model_get_iter (model, &iter, (GtkTreePath *)ptr->data))
		{
			gtk_tree_model_get (model, &iter,
					1, &path,
					-1);

			/* TODO: read tags */
			if ((tag = id3v1_new_from_path (path)) != NULL)
			{
				id3v1_dump (tag, stdout);
				gv1_read_from_id3v1 (gv1, tag);
			}
			else
			{
				g_message ("file: %s don't have Id3v1 tag\n", path);
			}
		}

	}
	else /* 2 or more rows are selected */
	{
		/* TODO: reset gv1, update some same field */
	}

	g_list_foreach (list, (GFunc)gtk_tree_path_free, NULL);
	g_list_free (list);
	g_free (path);
	id3v1_free (tag);
}

G_MODULE_EXPORT 
void on_list_insert (gpointer *widget, Id3e *id3e)
{
	GSList *pathlist;

	pathlist = get_path (GTK_WINDOW (id3e_get_window (id3e)),
			GTK_FILE_CHOOSER_ACTION_OPEN);
	
	if (pathlist != NULL)
	{
		GSList *ptr = pathlist;
		while (ptr != NULL)
		{
			id3e_list_insert (id3e, (gchar *)ptr->data);
			g_free (ptr->data);
			ptr = g_slist_next (ptr);
		}
		g_slist_free (pathlist);
	}
}

/* GtkTreePath -> GtkTreeRowReference -> GtkTreePath -> GtkTreeIter */
G_MODULE_EXPORT
void on_list_delete (gpointer *widget, Id3e *id3e)
{
	GtkTreeSelection *selection;
	GList *list;
	GList *ref_list = NULL;
	GList *ptr;
	GtkTreeRowReference *ref;
	GtkTreeModel *model;


	model = GTK_TREE_MODEL (id3e_get_list_store (id3e));
	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (id3e_get_list (id3e)));
	
	list = gtk_tree_selection_get_selected_rows (selection, 
			&model);

	/* convert GtkTreePath to GtkTreeRowReference */
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
void on_list_open (gpointer *widget, Id3e *id3e)
{
	GSList *pathlist;
	gchar *path;


	path = g_new (gchar, ID3E_PATH_LEN);
	pathlist = get_path (GTK_WINDOW (id3e_get_window (id3e)),
			GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);

	if (pathlist != NULL)
	{
		GSList *ptr = pathlist;
		while (ptr != NULL)
		{
			g_strlcpy (path, (gchar *)ptr->data, ID3E_PATH_LEN);
			listfile (id3e, path);
			g_free (ptr->data);
			ptr = g_slist_next (ptr);
		}
		g_slist_free (pathlist);
	}

	g_free (path);
}

G_MODULE_EXPORT 
void on_list_clear (gpointer *widget, Id3e *id3e)
{
	GtkListStore *liststore;

	liststore = id3e_get_list_store (id3e);
	gtk_list_store_clear (liststore);
}


G_MODULE_EXPORT 
void on_sidebar_toggle (gpointer *widget, Id3e *id3e)
{
	id3e_sidebar_toggle (id3e);
}

G_MODULE_EXPORT 
void on_statusbar_toggle (gpointer *widget, Id3e *id3e)
{
	id3e_statusbar_toggle (id3e);
}

G_MODULE_EXPORT
gboolean on_query_tooltip (GtkWidget *widget, gint x, gint y, gboolean keyboard_mode, GtkTooltip *tooltip, Id3e *id3e)
{
	GtkTreeIter iter;
	GtkTreeView *view = GTK_TREE_VIEW (widget);
	GtkTreeModel *model = GTK_TREE_MODEL (id3e_get_list_store (id3e));
	GtkTreePath *treepath = NULL;
	gchar *path;

	if (!gtk_tree_view_get_tooltip_context (view, &x, &y, 
				keyboard_mode, &model, &treepath, &iter))
	{
		return FALSE;
	}

	gtk_tree_model_get (model, &iter, 1, &path, -1);

	gtk_tooltip_set_text (tooltip, path);

	gtk_tree_view_set_tooltip_row (view, tooltip, treepath);

	gtk_tree_path_free (treepath);
	g_free (path);

	return TRUE;
}

G_MODULE_EXPORT
void on_edit_clicked (gpointer *widget, Id3e *id3e)
{
	Gv1 *gv1;
	gv1 = id3e_get_gv1 (id3e);
	gv1_set_sensitive (gv1, !(gv1_is_sensitive(gv1)));
}

G_MODULE_EXPORT
void on_save_clicked (gpointer *widget, Id3e *id3e)
{
	g_message ("on_save_clicked");
}

G_MODULE_EXPORT
void on_enc_changed (gpointer *widget, Id3e *id3e)
{
	g_message ("on_enc_changed");
}

G_MODULE_EXPORT
void on_enc_popdown (GtkComboBox *button, Id3e *id3e)
{
	g_message ("on_enc_popdown");
}

G_MODULE_EXPORT
void on_enc_editing_done (GtkCellEditable *celleditable, Id3e *id3e)
{
	g_message ("on_enc_editing_done");
}

G_MODULE_EXPORT
void on_convert_clicked (gpointer *widget, Id3e *id3e)
{
	g_message ("on_convert_clicked");
}

/* Private func */
static GSList *get_path (GtkWindow *parent, GtkFileChooserAction action)
{
	GtkWidget *chooser;
	GtkFileFilter *filter;
	GSList *pathlist = NULL;
	const gchar *homedir;

	homedir = g_get_home_dir ();

	chooser = gtk_file_chooser_dialog_new ("Select...",
			parent,
			action,
			GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, /* button, response_id */
			GTK_STOCK_OK, GTK_RESPONSE_OK,
			NULL);
	gtk_file_chooser_set_select_multiple (GTK_FILE_CHOOSER (chooser), TRUE);
	gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (chooser), homedir);
	
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
 * 		"E:\code\id3e\test/a.MP3"
 * windows use '\' as separator, but '/' still works.
*/
static void listfile (Id3e *id3e, gchar *path)
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
			id3e_list_insert (id3e, path);
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
		listfile (id3e, path);
	}

	ptr[-1] = 0;
	
	g_dir_close (dir);
}
