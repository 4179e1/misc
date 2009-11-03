#include <gtk/gtk.h>
#include "idve.h"
#include "debug_macro.h"

static gboolean init_app (Idve *idve);
static GObject *Gtk_builder_get_object (GtkBuilder *builder, const gchar *name);

int main (int argc, char *argv[])
{
	Idve *idve;
	GtkBuilder *builder;

	gtk_init (&argc, &argv);

	builder = gtk_builder_new ();

	idve = idve_new ();

	if (!init_app (idve))
	{
		idve_free (idve);
		return (1);
	}

	idve_window_show (idve);

	gtk_main ();

	idve_free (idve);

	return (0);
}

static gboolean init_app (Idve *idve)
{
	GtkBuilder *builder;
	GError *error = NULL;

	/* IMPORTENT, i always forget to initial it :( */
	builder = gtk_builder_new ();

	if (!gtk_builder_add_from_file (builder, "idve.glade", &error))
	{
		DEBUG_PRINT;
		g_warning ("%s", error->message);
		g_free (error);
		return FALSE;
	}

	idve_set_window (idve, 
			GTK_WIDGET (Gtk_builder_get_object (builder, "window")));
	idve_set_list (idve,
			GTK_WIDGET (Gtk_builder_get_object (builder, "list")));
	/* WTF the two lines are necessary to select multiple rows */
	GtkTreeSelection *selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (idve_get_list (idve)));
	gtk_tree_selection_set_mode (selection, GTK_SELECTION_MULTIPLE);

	idve_set_liststore (idve,
			GTK_LIST_STORE (Gtk_builder_get_object (builder, "liststore")));
	idve_set_sidebar (idve,
			GTK_WIDGET (Gtk_builder_get_object (builder, "notebook")));
	idve_set_statusbar (idve,
			GTK_WIDGET (Gtk_builder_get_object (builder, "statusbar")));
	idve_statusbar_init (idve);
	idve_statusbar_message (idve, "IDV Editor Ready!");

#if 1 /* testing code */
	idve_liststore_insert (idve, "abc");
	idve_liststore_insert (idve, "def");
#endif

	gtk_builder_connect_signals (builder, idve);

	g_object_unref (G_OBJECT (builder));

	return TRUE;
}

static GObject *Gtk_builder_get_object (GtkBuilder *builder, const gchar *name)
{
	GObject *obj;

	if ((obj = gtk_builder_get_object (builder, name)) == NULL)
	{
		g_warning ("gtk_builder_get_object: %s failed!", name);
	}

	return obj;
}
