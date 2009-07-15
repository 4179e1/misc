#include <gtk/gtk.h>
#include <stdlib.h>
#include "comman.h"
#include "dbb.h"
#include "file.h"

#define BUILDER_XML_FILE "dbb.xml"

int main(int argc, char *argv[])
{
	DataBaseBuilder *dbb;

	/* allocate memory need by DataBaseBuilder struct *dbb */
	dbb = g_slice_new(DataBaseBuilder);

	/* initialize gtk+ libraries */
	gtk_init(&argc, &argv);

	/* initialize data in struct */
	init_data(dbb);

	/* initialize gui*/
	if( !init_gui(dbb) )	//error loading gui
		exit(1);

	/* select wich database to edit, or open a new database */
	start(dbb);

	/* show the window */
	gtk_widget_show(dbb->window);

	/* enter gtk main loop */
	gtk_main();

	/* free the memory allocated for DataBaseBuilder *dbb */
	g_slice_free(DataBaseBuilder, dbb);

	exit(0);
}

/* initialize DataBaseBuilder struct *dbb /
 set default value of data in struct*/
void init_data(DataBaseBuilder *dbb)
{
	dbb->title = (char *) malloc(sizeof(char) * MAX_LENGTH);
	sprintf(dbb->title, "%s", PROG_TITLE);
	dbb->database_name = NULL;
	dbb->database_name_temp = NULL;
	dbb->need_saved = FALSE;
}

gboolean init_gui(DataBaseBuilder *dbb)
{
	GtkBuilder *builder;
	GError *err = NULL;

	/* use  GtkBuilder to build GUI from xml file */
	builder = gtk_builder_new();
	if(gtk_builder_add_from_file(builder, BUILDER_XML_FILE, &err) == 0)
	{
		g_print("gtkbuilder reading xml file error\n");
		return FALSE;
	}

	/* get the widgets which will be referenced in callbacks */
	dbb->window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
	gtk_window_set_title(GTK_WINDOW(dbb->window), dbb->title);

	/* connect signals, passing DataBaseBuilder struct as usr_data */
	gtk_builder_connect_signals(builder, dbb);

	/* free memory used by GtkBuilder */
	g_object_unref(G_OBJECT(builder));

	return TRUE;
}

void start(DataBaseBuilder *dbb)
{
	g_print("DEBUG: what's up?\n");

	on_file_new_activate(NULL, dbb);

	g_print("Debug: what's up?\n");

}
