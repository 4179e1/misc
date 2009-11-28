#include <gtk/gtk.h>
#include <string.h>
#include "list.h"
#include "gva.h"
#include "id3e.h"

/* same as linux */
#define ID3E_PATH_LEN 4096

static GSList *get_path (GtkWindow *parent, GtkFileChooserAction action);
static void listfile (Id3e *id3e, char* path);
static void set_id3_multi (GtkTreeModel *model, GtkTreePath *path, GtkTreeIter *iter, Id3 *mul);
static void selection_foreach_init (void);

G_MODULE_EXPORT
void on_selection_changed (GtkTreeSelection *selection, Id3e *id3e)
{
	gint selected_num;
	Gva *gva;
	Enc *enc;

	selected_num = gtk_tree_selection_count_selected_rows (selection);
	id3e_statusbar_message (id3e, "Selected %d rows", selected_num);
	enc = id3e_get_enc (id3e);
	gva = id3e_get_gva (id3e);
	gva_reset (gva);

	/* not thing selected */
	if (selected_num == 0)
	{
		/* TODO: reset gva */
		return;
	}
	else
	{
		/* ok, selected something, initial some variable */
		GList *list;
		GList *ptr;
		GtkTreeModel *model;
		GtkTreeIter iter;
		gchar *path = NULL;
		gchar *src;
		gboolean result;
		Id3 *tag;
		Id3 *tag_new;
	
		src = enc_get_src_text (enc);
		model = GTK_TREE_MODEL (id3e_get_list_store (id3e));
		list = gtk_tree_selection_get_selected_rows (selection,
				&model);
		ptr = list;
	

		if (gtk_tree_model_get_iter (model, &iter, (GtkTreePath *)ptr->data))
		{
			gtk_tree_model_get (model, &iter,
					1, &path,
					-1);
			if ((tag = id3_new_from_path (path)) != NULL)
			{
				if (selected_num == 1) /* only 1 row selected */
				{
					g_message ("selected 1 item");
					tag_new = id3_convert (tag, "UTF-8", src, &result);
					gva_read_from_id3 (gva, tag_new);
					id3_free (tag_new);
				}
				else /* two or more rows selected */
				{
					g_message ("selected %d items", selected_num);
					Id3 *mul;
					mul = id3_multi_new_from_tag (tag);
					/* TODO: a foreach func to set mul */
					selection_foreach_init ();
					gtk_tree_selection_selected_foreach (selection, (GtkTreeSelectionForeachFunc)set_id3_multi, mul);

					tag_new = id3_multi_convert (mul, "UTF-8", src, &result);
					gva_read_from_id3_multi (gva, tag_new);

					id3_free (mul);
				}

				id3_free (tag);
			}
		}

		if (!result)
		{
			id3e_statusbar_message (id3e, "Convert from %s to UTF-8 fail", src);
		}

		g_free (src);

		g_list_foreach (list, (GFunc)gtk_tree_path_free, NULL);
		g_list_free (list);
		g_free (path);
	}
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
	Gva *gva;

	liststore = id3e_get_list_store (id3e);
	gva = id3e_get_gva (id3e);
	gtk_list_store_clear (liststore);
	gva_reset (gva);
	gva_set_sensitive (gva, FALSE);
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
		g_error_free (error);
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

/* FIXME: need a better way to handle this, static varible are causing some problem */
static gboolean v1 = FALSE;
static gboolean v2 = FALSE;	/* TODO: PH for id3v2 */

void selection_foreach_init (void)
{
	v1 = FALSE;
	v2 = FALSE;
} 

static void set_id3_multi (GtkTreeModel *model, GtkTreePath *path, GtkTreeIter *iter, Id3 *mul)
{
	gchar *str;
	Id3v1Multi *mtag1;
	if (v1 || v2)
	{
		return;
	}

	mtag1 = (Id3v1Multi *)id3_get_id3v1 (mul);
	if (mtag1)
	{
		if (id3v1_multi_no_same (mtag1))
		{
			v1 = TRUE;
		}
		else
		{
			gtk_tree_model_get (model, iter, 1, &str, -1);
			/* let's see which field are same */
			id3v1_multi_set_from_path (mtag1, str);
			g_free (str);
		}
	}
	else
	{
		v1 = TRUE;
	}
	/* TODO: id3v2 */
}
