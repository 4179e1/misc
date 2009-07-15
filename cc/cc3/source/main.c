#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "../header/struct.h"
#include "../header/main.h"

int main(int argc, char *argv[])
{
	DataBaseBuilder *dbb;
	dbb = g_slice_new(DataBaseBuilder);

	gtk_init(&argc, &argv);

	if( init_app(dbb) == 1 )
		exit(1);

	gtk_widget_show(dbb->window);

	gtk_main();

	exit(0);
}
