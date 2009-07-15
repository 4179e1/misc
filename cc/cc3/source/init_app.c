#include <gtk/gtk.h>
#include "../header/init_app.h"
#include "../header/struct.h"
int init_app(DataBaseBuilder *dbb)
{
	GtkBuilder *builder;
	GError *err = NULL;

	builder = gtk_builder_new();
	if(gtk_builder_add_from_file(builder, BUILDER_XML_FILE, &err) == 0)
	{
		g_print("error\n");
		return 1;
	}

	dbb->window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

	gtk_builder_connect_signals(builder, dbb);

	g_object_unref(G_OBJECT(builder));

	return 0;
}
