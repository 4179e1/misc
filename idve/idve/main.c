#include <gtk/gtk.h>
#include "idve.h"
#include "debug_macro.h"

static gboolean init_app (Idve *idve);

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
	idve_set_statusbar (idve,
			GTK_WIDGET (Gtk_builder_get_object (builder, "statusbar")));
	idve_statusbar_init (idve);
	idve_statusbar_message (idve, "IDV Editor Ready!");

	gtk_builder_connect_signals (builder, idve);

	g_object_unref (G_OBJECT (builder));

	return TRUE;
}
