#include <gtk/gtk.h>
#include "callback.h"
#include "wrap.h"
#include "enc.h"
#include "gva.h"
#include "id3e.h"
#include "list.h"

/* struct for id3e, passed as the argument to all callback func  */
struct _id3e
{
	GtkWidget *window;

	GtkWidget *list;

	GtkWidget *sidebar;
	gboolean sidebar_is_shown;

	GtkWidget *statusbar;
	gboolean statusbar_is_shown;
	gint statusbar_context_id;

	Enc *enc;

	Gva *gva;

	gpointer pointer;
};


/* memory alloc */
Id3e *id3e_new (void)
{
	Id3e *id3e;

	id3e = g_slice_new (Id3e);
	id3e->window = NULL;

	id3e->list = NULL;

	id3e->sidebar = NULL;
	id3e->sidebar_is_shown = TRUE;

	id3e->statusbar = NULL;
	id3e->statusbar_is_shown = TRUE;

	id3e->pointer = NULL;
	
	id3e->enc = enc_new ();

	id3e->gva = gva_new ();

	return id3e;
}

void id3e_free (Id3e *id3e)
{
	enc_free (id3e->enc);
	gva_free (id3e->gva);
	g_slice_free (Id3e, id3e);
}

Id3e *id3e_init (Id3e *id3e, GtkBuilder *builder)
{
	id3e_set_window (id3e, 
			GTK_WIDGET (Gtk_builder_get_object (builder, "window")));
	id3e_set_list (id3e,
			GTK_WIDGET (Gtk_builder_get_object (builder, "list")));
	id3e_list_init (id3e);


	id3e_set_sidebar (id3e,
			GTK_WIDGET (Gtk_builder_get_object (builder, "notebook")));
	id3e_set_statusbar (id3e,
			GTK_WIDGET (Gtk_builder_get_object (builder, "statusbar")));
	id3e_statusbar_init (id3e);

	enc_init (id3e->enc, builder);
	/** 
	 * however, Enc cannot completely initial itsert
	 * without some help from Id3e. it need a pointer to Id3e,
	 * but enc know nothing about Id3e.
	 */
	g_signal_connect (enc_get_src_entry (id3e->enc), "activate", G_CALLBACK (on_enc_activate), id3e);
	
#if 0
	/**
	 * the dest entry don't need this signal,
	 * while complete input in src, we should refresh gva,
	 * but dest don't refresh gva;
	 */
	g_signal_connect (enc_get_dest_entry (id3e->enc), "activate", G_CALLBACK (on_enc_activate), id3e);
#endif

	gva_init (id3e->gva, builder);

	return id3e;
}
/* window */
void id3e_set_window (Id3e *id3e, GtkWidget *window)
{
	id3e->window = window;
}

GtkWidget *id3e_get_window (Id3e *id3e)
{
	return id3e->window;
}

void id3e_window_show (Id3e *id3e)
{
	gtk_widget_show (GTK_WIDGET (id3e->window));
}

/* listview */
void id3e_set_list (Id3e *id3e, GtkWidget *list)
{
	id3e->list = list;
}

GtkWidget *id3e_get_list (Id3e *id3e)
{
	return id3e->list;
}

void id3e_list_init (Id3e *id3e)
{
	GtkTreeViewColumn *name_col;
	GtkTreeSelection *selection;
	GtkTreeView *treeview = GTK_TREE_VIEW (id3e->list);

	name_col = gtk_tree_view_get_column (treeview, 0);
	gtk_tree_view_column_set_sort_column_id (name_col, 0);

	/* WTF the two lines are necessary to select multiple rows */
	selection = gtk_tree_view_get_selection (treeview);
	gtk_tree_selection_set_mode (selection, GTK_SELECTION_MULTIPLE);
	g_signal_connect (selection, "changed", G_CALLBACK (on_selection_changed), id3e);
}

GtkListStore *id3e_get_list_store (Id3e *id3e)
{
	GtkTreeModel *model;
	model = gtk_tree_view_get_model (GTK_TREE_VIEW (id3e->list));
	return GTK_LIST_STORE (model);
}

void id3e_list_insert (Id3e *id3e, const gchar *path)
{
	GtkTreeIter iter;
	gchar *name;
	GtkListStore *liststore;

	liststore= GTK_LIST_STORE (gtk_tree_view_get_model (GTK_TREE_VIEW (id3e->list)));
	name = g_path_get_basename (path);

	gtk_list_store_append (liststore, &iter);
	gtk_list_store_set (liststore, &iter,
			0, name,
			1, path,
			-1);

	g_free (name);
}

gint id3e_list_get_selected_count (Id3e *id3e)
{
	GtkTreeSelection *selection;
	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (id3e->list));
	return gtk_tree_selection_count_selected_rows (selection);
}

GList *id3e_list_get_selectd_rows (Id3e *id3e)
{
	GtkTreeSelection *selection;
	GtkTreeModel *model;
	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (id3e->list));
	model = gtk_tree_view_get_model (GTK_TREE_VIEW (id3e->list));
	return gtk_tree_selection_get_selected_rows (selection, &model);
}
/* sidebar */
void id3e_set_sidebar (Id3e *id3e, GtkWidget *sidebar)
{
	id3e->sidebar = sidebar;
}

GtkWidget *id3e_get_sidebar (Id3e *id3e)
{
	return id3e->sidebar;
}

void id3e_sidebar_toggle (Id3e *id3e)
{
	if (id3e->sidebar_is_shown)
	{
		gtk_widget_hide (id3e->sidebar);
		id3e->sidebar_is_shown = FALSE;
	}
	else
	{
		gtk_widget_show (id3e->sidebar);
		id3e->sidebar_is_shown = TRUE;
	}
}

/* statusbar */
void id3e_set_statusbar (Id3e *id3e, GtkWidget *statusbar)
{
	id3e->statusbar = statusbar;
}

GtkWidget *id3e_get_statusbar (Id3e *id3e)
{
	return id3e->statusbar;
}

void id3e_statusbar_init (Id3e *id3e)
{
	char *msg = "ID3 Editor Ready!";
	id3e->statusbar_context_id = gtk_statusbar_get_context_id (GTK_STATUSBAR (id3e->statusbar), msg);
	gtk_statusbar_push (GTK_STATUSBAR (id3e->statusbar), id3e->statusbar_context_id, msg);
	id3e->statusbar_context_id = gtk_statusbar_get_context_id (GTK_STATUSBAR (id3e->statusbar), msg);
	gtk_statusbar_push (GTK_STATUSBAR (id3e->statusbar), id3e->statusbar_context_id, msg);
}

void id3e_statusbar_message (Id3e *id3e, const char *fmt, ...)
{
	gchar *msg;
	va_list ap;

	va_start (ap, fmt);
	msg = g_strdup_vprintf (fmt, ap);
	va_end (ap);

	gtk_statusbar_pop (GTK_STATUSBAR (id3e->statusbar), 
			id3e->statusbar_context_id);
	gtk_statusbar_push (GTK_STATUSBAR (id3e->statusbar),
			id3e->statusbar_context_id, msg);

	g_free (msg);
}

void id3e_statusbar_toggle (Id3e *id3e)
{
	if (id3e->statusbar_is_shown)
	{
		gtk_widget_hide (id3e->statusbar);
		id3e->statusbar_is_shown = FALSE;
	}
	else
	{
		gtk_widget_show (id3e->statusbar);
		id3e->statusbar_is_shown = TRUE;
	}
}

/* enc */

void id3e_set_enc (Id3e *id3e, Enc *enc)
{
	id3e->enc = enc;
}

Enc *id3e_get_enc (Id3e *id3e)
{
	return id3e->enc;
}

/* gva */
void id3e_set_gva (Id3e *id3e, Gva *gva)
{
	id3e->gva = gva;
}

Gva *id3e_get_gva (Id3e *id3e)
{
	return id3e->gva;
}

/* pointer for some func only accept certain number of parmas, very ugly designs in fact */
gpointer id3e_pointer_aquire (Id3e *id3e, gpointer data)
{
	if (id3e->pointer != NULL)
	{
		g_warning ("pointer not available now, try again later");
		return NULL;
	}

	id3e->pointer = data;
	return id3e->pointer;
}

gpointer id3e_pointer_release (Id3e *id3e)
{
	gpointer tmp = id3e->pointer;
	id3e->pointer = NULL;
	return tmp;
}

gpointer id3e_get_pointer (Id3e *id3e)
{
	return id3e->pointer;
}

gboolean id3e_pointer_is_available (Id3e *id3e)
{
	return (id3e->pointer == NULL);
}
