#include <gtk/gtk.h>
#include <stdlib.h>
#include "reg.h"
#include "treeview.h"
#include "listview.h"
#include "menu.h"

int main (int argc, char *argv[]) {
	Reg *reg;
	reg = g_slice_new (Reg);
	if (reg == NULL)
	{
		fprintf (stderr, "Error: not engouh space\n");
		exit (1);
	}

	reg->path = malloc (sizeof (char) * MAX_VALUE_NAME);
	if (reg->path == NULL)
	{
		fprintf (stderr, "Error: not engouh space\n");
		exit (1);
	}

	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *menubar;
	GtkWidget *sw;
	GtkWidget *hpaned;
	GtkWidget *treeview;
	GtkWidget *listview;
	GtkWidget *statusbar;

	GtkTreeSelection *selection;

	GtkWidget *file;
	GtkWidget *edit;
	GtkWidget *option;

	GtkWidget *filemenu;
	GtkWidget *file_quit;

	GtkWidget *editmenu;
	GtkWidget *edit_insert_reg_sz;
	GtkWidget *edit_delete_key;

	GtkWidget *optionmenu;
	GtkWidget *option_add_to_run;
	GtkWidget *option_bind_gateway;

	gtk_init (&argc, &argv);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "注册表编辑器");
	gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size (GTK_WINDOW (window), 600, 400);

	vbox = gtk_vbox_new (FALSE, 0);
	gtk_container_add (GTK_CONTAINER (window), vbox);

	menubar = gtk_menu_bar_new();
	gtk_box_pack_start (GTK_BOX (vbox), menubar, FALSE, FALSE, 0);

	hpaned = gtk_hpaned_new ();
	gtk_box_pack_start (GTK_BOX (vbox), hpaned, TRUE, TRUE, 0);

	sw = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (sw), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_paned_add1 (GTK_PANED (hpaned), sw);

	treeview = create_tree_view_and_model();
	gtk_container_add (GTK_CONTAINER (sw), treeview);
	gtk_widget_set_size_request (treeview, 150, 0);

	sw = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (sw), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_paned_add2 (GTK_PANED (hpaned), sw);

	listview = create_list_view_and_model();
	gtk_container_add (GTK_CONTAINER (sw), listview);
	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (listview));

	statusbar = gtk_statusbar_new();
	gtk_box_pack_start (GTK_BOX (vbox), statusbar, FALSE, FALSE, 0);

	file = gtk_menu_item_new_with_mnemonic ("_File");
	edit = gtk_menu_item_new_with_mnemonic ("_Edit");
	option = gtk_menu_item_new_with_mnemonic ("_Option");
	gtk_menu_shell_append (GTK_MENU_SHELL (menubar), file);
	gtk_menu_shell_append (GTK_MENU_SHELL (menubar), edit);
	gtk_menu_shell_append (GTK_MENU_SHELL (menubar), option);

	filemenu = gtk_menu_new();
	editmenu = gtk_menu_new();
	optionmenu = gtk_menu_new();
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (file), filemenu);
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (edit), editmenu);
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (option), optionmenu);

	file_quit = gtk_image_menu_item_new_from_stock (GTK_STOCK_QUIT, NULL);
	gtk_menu_shell_append (GTK_MENU_SHELL (filemenu), file_quit);

	edit_insert_reg_sz = gtk_menu_item_new_with_label ("插入键值(REG_SZ)");
	edit_delete_key = gtk_menu_item_new_with_label ("删除选定键值");
	gtk_menu_shell_append (GTK_MENU_SHELL (editmenu), edit_insert_reg_sz);
	gtk_menu_shell_append (GTK_MENU_SHELL (editmenu), edit_delete_key);

	option_add_to_run = gtk_menu_item_new_with_label ("加入启动项");
	option_bind_gateway = gtk_menu_item_new_with_label ("绑定网关");
	gtk_menu_shell_append (GTK_MENU_SHELL (optionmenu), option_add_to_run);
	gtk_menu_shell_append (GTK_MENU_SHELL (optionmenu), option_bind_gateway);

	reg->rootkey = HKEY_CLASSES_ROOT;
	reg->path[0] = '\0';
	reg->treeview = treeview;
	reg->listview = listview;
	reg->selection = selection;
	reg->progname = argv[0];

	gtk_widget_show_all (window);

	g_signal_connect_swapped (G_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit), G_OBJECT (window));

	g_signal_connect (GTK_TREE_VIEW (treeview), "row-activated", G_CALLBACK (on_tree_view_row_activated), reg);

	g_signal_connect (GTK_MENU_ITEM (file_quit), "activate", G_CALLBACK (gtk_main_quit), NULL);
	g_signal_connect (GTK_MENU_ITEM (edit_insert_reg_sz), "activate", G_CALLBACK (on_edit_insert_reg_sz_activate), reg);
	g_signal_connect (GTK_MENU_ITEM (edit_delete_key), "activate", G_CALLBACK (on_edit_delete_key_activate), reg);
	g_signal_connect (GTK_MENU_ITEM (option_add_to_run), "activate", G_CALLBACK (on_option_add_to_run_activate), reg);
	g_signal_connect (GTK_MENU_ITEM (option_bind_gateway), "activate", G_CALLBACK (on_option_bind_gateway_activate), reg);

//	g_signal_connect (selection, "changed", G_CALLBACK (on_changed), collection);

	gtk_main();	

	free (reg->path);
	g_slice_free (Reg, reg);

	return 0;
}
