#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "main.h"

int main(int argc, char *argv[])
{
	GtkWidget *window;
	window = g_slice_new(GtkWidget);

	gtk_init(&argc, &argv);

	if( !init_app(&window) )
		exit(1);

	gtk_widget_show(window);

	gtk_main();

	exit(0);
}
