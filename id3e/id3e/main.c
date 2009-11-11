#include <gtk/gtk.h>
#include "id3e.h"
#include "gv1.h"
#include "wrap.h"
#include "debug_macro.h"

static gboolean init_app (Id3e *id3e);

int main (int argc, char *argv[])
{
	Id3e *id3e;
	GtkBuilder *builder;

	gtk_init (&argc, &argv);

	builder = gtk_builder_new ();

	id3e = id3e_new ();

	if (!init_app (id3e))
	{
		g_print ("init_app failed\n");
		id3e_free (id3e);
		return (1);
	}

	id3e_window_show (id3e);

	gtk_main ();

	id3e_free (id3e);

	return (0);
}

static gboolean init_app (Id3e *id3e)
{
	GtkBuilder *builder;
	GError *error = NULL;

	/* IMPORTENT, i always forget to initial it :( */
	builder = gtk_builder_new ();

	if (!gtk_builder_add_from_file (builder, "id3e.glade", &error))
	{
		DEBUG_PRINT;
		g_warning ("%s", error->message);
		g_free (error);
		return FALSE;
	}

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


	gv1_init (builder);


	gtk_builder_connect_signals (builder, id3e);

	g_object_unref (G_OBJECT (builder));

	return TRUE;
}
