#include <gtk/gtk.h>
#include "idvc.h"
#include "idvc_menu.h"

GtkWidget *idvc_menu_new (Idvc *idvc_data)
{
	GtkWidget *menubar;
	GtkWidget *fileitem;
	GtkWidget *filemenu;
	GtkWidget *quit;

	menubar = gtk_menu_bar_new ();
	fileitem = gtk_menu_item_new_with_mnemonic ("_File");
	gtk_menu_shell_append (GTK_MENU_SHELL (menubar), fileitem);

	filemenu = gtk_menu_new ();
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (fileitem), filemenu);
	quit = gtk_image_menu_item_new_from_stock (GTK_STOCK_QUIT, NULL);
	gtk_menu_shell_append (GTK_MENU_SHELL (filemenu), quit);

	return menubar;
}
