#include <gtk/gtk.h>
#include "idvc.h"
#include "idvc_list.h"

static void gui_init (Idvc *idvc_info);

int main (int argc, char *argv[])
{
	Idvc *idvc_info;

	gtk_init (&argc, &argv);

	idvc_info = idvc_new ();

	gui_init (idvc_info);

	gtk_widget_show_all (idvc_get_window (idvc_info));

	gtk_main();

	idvc_free (idvc_info);

	return 0;
}

#define IDVC_SPACING 2
#define IDVC_PADDING 0
static void gui_init (Idvc *idvc_info)
{
	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *hpaned;
	GtkWidget *list;
	GtkWidget *notebook;
	GtkWidget *statusbar;

	GtkWidget *menubar;
	GtkWidget *fileitem;
	GtkWidget *filemenu;
	GtkWidget *quit;

	GtkWidget *toolbar;
	GtkToolItem *bt_add;
	GtkToolItem *bt_directory;
	GtkToolItem *bt_remove;
	GtkToolItem *bt_clear;
	GtkToolItem *bt_hide;
	GtkToolItem *bt_quit;
	GtkToolItem *bt_sep;

	GtkWidget *sw_idv1;
	GtkWidget *sw_idv2;
	GtkWidget *label;

/* window */
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "IDV Converter");
	gtk_window_set_default_size (GTK_WINDOW (window), 600, 400);
	g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit), NULL);
	idvc_set_window (idvc_info, window);

/* vbox */
	vbox = gtk_vbox_new (FALSE, IDVC_SPACING);
	gtk_container_add (GTK_CONTAINER (window), vbox);

/* menu */
	menubar = gtk_menu_bar_new ();
	gtk_box_pack_start (GTK_BOX(vbox), menubar, FALSE, FALSE, IDVC_PADDING);
	fileitem = gtk_menu_item_new_with_mnemonic ("_File");
	gtk_menu_shell_append (GTK_MENU_SHELL (menubar), fileitem);

	filemenu = gtk_menu_new ();
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (fileitem), filemenu);
	quit = gtk_image_menu_item_new_from_stock (GTK_STOCK_QUIT, NULL);
	gtk_menu_shell_append (GTK_MENU_SHELL (filemenu), quit);

/* toolbar */
	toolbar = gtk_toolbar_new ();
	gtk_box_pack_start (GTK_BOX (vbox), toolbar, FALSE, FALSE, IDVC_PADDING);

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

/* hpaned */
	hpaned = gtk_hpaned_new ();
	gtk_paned_set_position (GTK_PANED (hpaned), 400);
	gtk_box_pack_start (GTK_BOX (vbox), hpaned, TRUE, TRUE, IDVC_PADDING);

/* list */
	list = idvc_list_new ();
	gtk_paned_add1 (GTK_PANED (hpaned), list);
	idvc_set_list (idvc_info, list);

/* notebook */
	notebook = gtk_notebook_new ();
	gtk_paned_add2 (GTK_PANED (hpaned), notebook);

	sw_idv1 = gtk_scrolled_window_new (NULL, NULL);
	label = gtk_label_new ("IDV1");
	gtk_notebook_append_page (GTK_NOTEBOOK (notebook), sw_idv1, label);

	sw_idv2 = gtk_scrolled_window_new (NULL, NULL);
	label = gtk_label_new ("IDV2");
	gtk_notebook_append_page (GTK_NOTEBOOK (notebook), sw_idv2, label);

/* statusbar */
	statusbar = gtk_statusbar_new ();
	gtk_box_pack_start (GTK_BOX (vbox), statusbar, FALSE, FALSE, IDVC_PADDING);
	idvc_set_statusbar (idvc_info, statusbar);
}
