#include <gtk/gtk.h>
#include "idvc.h"
#include "idvc_toolbar.h"

GtkWidget *idvc_toolbar_new (Idvc *idvc_data)
{
	GtkWidget *toolbar;
	GtkToolItem *bt_add;
	GtkToolItem *bt_directory;
	GtkToolItem *bt_remove;
	GtkToolItem *bt_clear;
	GtkToolItem *bt_hide;
	GtkToolItem *bt_quit;
	GtkToolItem *bt_sep;

	toolbar = gtk_toolbar_new ();

	bt_add = gtk_tool_button_new_from_stock (GTK_STOCK_ADD);
	gtk_toolbar_insert (GTK_TOOLBAR (toolbar), bt_add, -1);

	bt_remove = gtk_tool_button_new_from_stock (GTK_STOCK_REMOVE);
	gtk_toolbar_insert (GTK_TOOLBAR (toolbar), bt_remove, -1);

	bt_sep = gtk_separator_tool_item_new ();
	gtk_toolbar_insert (GTK_TOOLBAR (toolbar), bt_sep, -1);

	bt_directory = gtk_tool_button_new_from_stock (GTK_STOCK_DIRECTORY);
	gtk_toolbar_insert (GTK_TOOLBAR (toolbar), bt_directory, -1);
	
	bt_clear = gtk_tool_button_new_from_stock (GTK_STOCK_CLEAR);
	gtk_toolbar_insert (GTK_TOOLBAR (toolbar), bt_clear, -1);

	bt_sep = gtk_separator_tool_item_new ();
	gtk_toolbar_insert (GTK_TOOLBAR (toolbar), bt_sep, -1);

	bt_hide = gtk_tool_button_new_from_stock (GTK_STOCK_CLOSE);
	gtk_toolbar_insert (GTK_TOOLBAR (toolbar), bt_hide, -1);

	bt_quit = gtk_tool_button_new_from_stock (GTK_STOCK_QUIT);
	gtk_toolbar_insert (GTK_TOOLBAR (toolbar), bt_quit, -1);

	return toolbar;
}
