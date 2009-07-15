#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

void toggle_statusbar(GtkWidget *widget, gpointer statusbar)
{
	if (gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(widget))) {
		gtk_widget_show(statusbar);
	} else {
		gtk_widget_hide(statusbar);
	}
}

void undo_redo(GtkWidget *widget,  gpointer item) 
{
  static int count = 2;
  const char *name = gtk_widget_get_name(widget);

  if ( strcmp(name, "undo") ) {
    count++;
  } else {
    count--;
  }
 
  if (count < 0) {
     gtk_widget_set_sensitive(widget, FALSE);
     gtk_widget_set_sensitive(item, TRUE);
  } 

  if (count > 5) {
     gtk_widget_set_sensitive(widget, FALSE);
     gtk_widget_set_sensitive(item, TRUE);
  }
}

int main(int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *vbox;
	
	GtkWidget *menubar;
	GtkWidget *file;
	GtkWidget *view;

	GtkWidget *filemenu;
	GtkWidget *new;
	GtkWidget *open;
	GtkWidget *sep;
	GtkWidget *quit;

	GtkWidget *viewmenu;
	GtkWidget *tog_stat;

	GtkWidget *toolbar;
	GtkToolItem *bt_new;
	GtkToolItem *bt_open;
	GtkToolItem *bt_save;
	GtkToolItem *undo;
	GtkToolItem *redo;
	GtkToolItem *bt_sep;
	GtkToolItem *bt_exit;

	GtkWidget *statusbar;

	GtkAccelGroup *accel_group = NULL;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 250, 200);
	gtk_window_set_title(GTK_WINDOW(window), "Menu");

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	menubar = gtk_menu_bar_new();
	filemenu = gtk_menu_new();
	viewmenu = gtk_menu_new();

	accel_group = gtk_accel_group_new();
	gtk_window_add_accel_group(GTK_WINDOW(window), accel_group);

	//File
	file = gtk_menu_item_new_with_mnemonic("_File");
	new = gtk_image_menu_item_new_from_stock(GTK_STOCK_NEW, NULL);
	open = gtk_image_menu_item_new_from_stock(GTK_STOCK_OPEN, NULL);
	sep = gtk_separator_menu_item_new();
	quit = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT, accel_group);

	gtk_widget_add_accelerator(quit, "activate", accel_group, GDK_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), new);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), open);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), sep);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);

	//View
	view = gtk_menu_item_new_with_mnemonic("_View");
	tog_stat = gtk_check_menu_item_new_with_mnemonic("Status _Bar");
	gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(tog_stat), TRUE);

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(view), viewmenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(viewmenu), tog_stat);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), view);

	//main window
	gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

	statusbar = gtk_statusbar_new();
	gtk_box_pack_end(GTK_BOX(vbox), statusbar, FALSE, TRUE, 1);

	toolbar = gtk_toolbar_new();
	gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);

	//toolbar
	gtk_container_set_border_width(GTK_CONTAINER(toolbar), 0);

  	bt_new = gtk_tool_button_new_from_stock(GTK_STOCK_NEW);
  	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), bt_new, -1);

	bt_open = gtk_tool_button_new_from_stock(GTK_STOCK_OPEN);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), bt_open, -1);

	bt_save = gtk_tool_button_new_from_stock(GTK_STOCK_SAVE);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), bt_save, -1);

	undo = gtk_tool_button_new_from_stock(GTK_STOCK_UNDO);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), undo, -1);

	redo = gtk_tool_button_new_from_stock(GTK_STOCK_REDO);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), redo, -1);

	bt_sep = gtk_separator_tool_item_new();
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), bt_sep, -1);

	bt_exit = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), bt_exit, -1);

	gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 0);

//	g_signal_connect_swapped(G_OBJECT(bt_exit), "clicked", G_CALLBACK(gtk_main_quit), NULL);

	//callback func
	g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	g_signal_connect(G_OBJECT(undo), "clicked", G_CALLBACK(undo_redo), redo);

	g_signal_connect(G_OBJECT(redo), "clicked", G_CALLBACK(undo_redo), undo);


//	g_signal_connect(G_OBJECT(quit), "activate", G_CALLBACK(gtk_main_quit), NULL);
	
	g_signal_connect(G_OBJECT(tog_stat), "activate", G_CALLBACK(toggle_statusbar), statusbar);

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}
