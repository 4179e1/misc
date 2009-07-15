#include <gtk/gtk.h>
#include "init_app.h"
#include "struct.h"
gboolean init_app(GtkWidget **window)
{
	GtkBuilder *builder;
	GError *err = NULL;

	builder = gtk_builder_new();
	if(gtk_builder_add_from_file(builder, BUILDER_XML_FILE, &err) == 0)
	{
		g_print("error\n");
		return FALSE;
	}

	*window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

	gtk_builder_connect_signals(builder, NULL);

	g_object_unref(G_OBJECT(builder));

	return TRUE;
}
