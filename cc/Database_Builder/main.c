#include <gtk/gtk.h>
#include <stdlib.h>
#include "database_builder.h"
#include "main.h"
#include "file_menu.h"
#include "edit_menu.h"
#include "debug_menu.h"
#include "other.h"
#include "handler.h"
#include "tree.h"

int main(int argc, char *argv[])
{
	afaf;
	DatabaseBuilder *builder;

	/* allocate the memory needed by DatabaseBuilder */
	builder = g_slice_new (DatabaseBuilder);
	builder->si = g_slice_new (SensitiveItem);

	/* initialize GTK+ libraries */
	gtk_init (&argc, &argv);

	if (!init_app (builder))
		exit(1);

	/* show the window */
	gtk_widget_show_all (builder->window);

	/* enter GTK+ main loop */
	gtk_main();

	/* free memory allocated for DatabaseBuiler */
	g_slice_free (SensitiveItem, builder->si);
	g_slice_free (DatabaseBuilder, builder);

	exit(0);
}


static GtkWidget * add_page (GtkWidget *notebook, const gchar *text)
{
	GtkWidget *sw;
	GtkWidget *label;
	GtkWidget *tree_view;

	label = gtk_label_new (text);
	sw = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (sw), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_notebook_append_page (GTK_NOTEBOOK (notebook), sw, label);

	tree_view = gtk_tree_view_new();
	gtk_tree_view_set_rules_hint (GTK_TREE_VIEW (tree_view), TRUE);
	gtk_container_add (GTK_CONTAINER (sw), tree_view);

	return tree_view;
}


gboolean init_app(DatabaseBuilder *builder)
{
	gint		id;

	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *menubar;
	GtkWidget *toolbar;
	GtkWidget *notebook;
	GtkWidget *statusbar;

	GtkWidget *file;
	GtkWidget *edit;
	GtkWidget *debug;
	GtkWidget *help;

	GtkWidget *filemenu;
	GtkWidget *file_new;
	GtkWidget *file_open;
	GtkWidget *sep;
	GtkWidget *file_close;
	GtkWidget *file_quit;

	GtkWidget *editmenu;
	GtkWidget *edit_add;
	GtkWidget *edit_edit;
	GtkWidget *edit_delete;
	GtkWidget *debugmenu;
	GtkWidget *debug_exec_sql_command;
	GtkWidget *helpmenu;
	GtkWidget *help_about;

	GtkToolItem *tool_button_add;
	GtkToolItem *tool_button_edit;
	GtkToolItem *tool_button_delete;


	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "Database Builder");
	gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size (GTK_WINDOW (window), 600, 400);
	gtk_window_set_default_icon_name (GTK_STOCK_INDEX);

	vbox = gtk_vbox_new (FALSE, 0);
	gtk_container_add (GTK_CONTAINER (window), vbox);

	menubar = gtk_menu_bar_new();
	gtk_box_pack_start (GTK_BOX (vbox), menubar, FALSE, FALSE, 0);

	toolbar = gtk_toolbar_new();
	gtk_toolbar_set_style (GTK_TOOLBAR (toolbar), GTK_TOOLBAR_BOTH_HORIZ);
	gtk_box_pack_start (GTK_BOX (vbox), toolbar, FALSE, FALSE, 0);

	notebook = gtk_notebook_new();
	gtk_notebook_set_scrollable (GTK_NOTEBOOK (notebook), TRUE);
	gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook), GTK_POS_RIGHT);
	gtk_box_pack_start (GTK_BOX (vbox), notebook, TRUE, TRUE, 0);

	statusbar = gtk_statusbar_new();
	gtk_box_pack_start (GTK_BOX (vbox), statusbar, FALSE, FALSE, 0);

	file = gtk_menu_item_new_with_mnemonic ("_File");
	edit = gtk_menu_item_new_with_mnemonic ("_Edit");
	debug = gtk_menu_item_new_with_mnemonic ("_Debug");
	help = gtk_menu_item_new_with_mnemonic ("_Help");
	gtk_menu_shell_append (GTK_MENU_SHELL (menubar), file);
	gtk_menu_shell_append (GTK_MENU_SHELL (menubar), edit);
	gtk_menu_shell_append (GTK_MENU_SHELL (menubar), debug);
	gtk_menu_shell_append (GTK_MENU_SHELL (menubar), help);

	filemenu = gtk_menu_new();
	editmenu = gtk_menu_new();
	debugmenu = gtk_menu_new();
	helpmenu = gtk_menu_new();
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (file), filemenu);
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (edit), editmenu);
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (debug), debugmenu);
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (help), helpmenu);

	file_new = gtk_image_menu_item_new_from_stock(GTK_STOCK_NEW, NULL);
	file_open = gtk_image_menu_item_new_from_stock(GTK_STOCK_OPEN, NULL);
	sep = gtk_separator_menu_item_new();
	file_close = gtk_image_menu_item_new_from_stock(GTK_STOCK_CLOSE, NULL);
	file_quit = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT, NULL);
	gtk_menu_shell_append (GTK_MENU_SHELL (filemenu), file_new);
	gtk_menu_shell_append (GTK_MENU_SHELL (filemenu), file_open);
	gtk_menu_shell_append (GTK_MENU_SHELL (filemenu), sep);
	gtk_menu_shell_append (GTK_MENU_SHELL (filemenu), file_close);
	gtk_menu_shell_append (GTK_MENU_SHELL (filemenu), file_quit);

	edit_add = gtk_image_menu_item_new_from_stock (GTK_STOCK_ADD, NULL);
	edit_edit = gtk_image_menu_item_new_from_stock (GTK_STOCK_EDIT, NULL);
	edit_delete = gtk_image_menu_item_new_from_stock (GTK_STOCK_DELETE, NULL);
	gtk_menu_shell_append (GTK_MENU_SHELL (editmenu), edit_add);
	gtk_menu_shell_append (GTK_MENU_SHELL (editmenu), edit_edit);
	gtk_menu_shell_append (GTK_MENU_SHELL (editmenu), edit_delete);

	debug_exec_sql_command = gtk_menu_item_new_with_mnemonic("_Exec sql command");
	gtk_menu_shell_append (GTK_MENU_SHELL (debugmenu), debug_exec_sql_command);

	help_about = gtk_image_menu_item_new_from_stock (GTK_STOCK_ABOUT, NULL);
	gtk_menu_shell_append (GTK_MENU_SHELL (helpmenu), help_about);

	tool_button_add = gtk_tool_button_new_from_stock (GTK_STOCK_ADD);
	tool_button_edit = gtk_tool_button_new_from_stock (GTK_STOCK_EDIT);
	tool_button_delete = gtk_tool_button_new_from_stock (GTK_STOCK_DELETE);
	gtk_toolbar_insert (GTK_TOOLBAR (toolbar), tool_button_add, -1);
	gtk_toolbar_insert (GTK_TOOLBAR (toolbar), tool_button_edit, -1);
	gtk_toolbar_insert (GTK_TOOLBAR (toolbar), tool_button_delete, -1);


/* initialize the DatabaseBuilder struct */
	builder->tree_view_race = add_page(notebook, "Race");
	builder->tree_view_class = add_page(notebook, "Class");
	builder->tree_view_skills = add_page(notebook, "Skills");
	builder->tree_view_feats = add_page(notebook, "Feats");
	builder->tree_view_powers = add_page(notebook, "Powers");
	builder->tree_view_equipment = add_page(notebook, "Equipment");
	builder->tree_view_alignment = add_page(notebook, "Aligment");
	builder->tree_view_deities = add_page(notebook, "Deities");

	init_alignment(builder->tree_view_alignment);
	//	add_to_alignment(tree_view_alignment, "ne", "oops");

	builder->page_index = 0;
	builder->tree_view_cur = builder->tree_view_race;

	builder->window = window;
	builder->statusbar = statusbar;
	
	builder->si->edit_add = edit_add;
	builder->si->edit_edit = edit_edit;
	builder->si->edit_delete = edit_delete;
	builder->si->debug_exec_sql_command = debug_exec_sql_command;
	builder->si->file_close = file_close;
	builder->si->tool_button_add = tool_button_add;
	builder->si->tool_button_edit = tool_button_edit;
	builder->si->tool_button_delete = tool_button_delete;

	builder->filename = NULL;
	builder->database = NULL;
	builder->selection = NULL;
/* initialize struct complete */


/* signal & callbakc functions */
	g_signal_connect_swapped (G_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit), G_OBJECT (window));

	g_signal_connect (GTK_MENU_ITEM (file_new), "activate", G_CALLBACK (on_file_new_activate), builder);
	g_signal_connect (GTK_MENU_ITEM (file_open), "activate", G_CALLBACK (on_file_open_activate), builder);
	g_signal_connect (GTK_MENU_ITEM (file_close), "activate", G_CALLBACK (on_file_close_activate), builder);
	g_signal_connect (GTK_MENU_ITEM (file_quit), "activate", G_CALLBACK (on_file_quit_activate), builder);

	g_signal_connect (GTK_MENU_ITEM (edit_add), "activate", G_CALLBACK (on_edit_add_activate), builder);
	g_signal_connect (GTK_MENU_ITEM (edit_edit), "activate", G_CALLBACK (on_edit_edit_activate), builder);
	g_signal_connect (GTK_MENU_ITEM (edit_delete), "activate", G_CALLBACK (on_edit_delete_activate), builder);

	g_signal_connect (GTK_MENU_ITEM (debug_exec_sql_command), "activate", G_CALLBACK (on_debug_exec_sql_command_activate), builder);

	g_signal_connect (GTK_MENU_ITEM (help_about), "activate", G_CALLBACK (on_help_about_activate), builder);

	g_signal_connect (GTK_TOOL_BUTTON (tool_button_add), "clicked", G_CALLBACK (on_tool_button_add_clicked), builder);
	g_signal_connect (GTK_TOOL_BUTTON (tool_button_edit), "clicked", G_CALLBACK (on_tool_button_edit_clicked), builder);
	g_signal_connect (GTK_TOOL_BUTTON (tool_button_delete), "clicked", G_CALLBACK (on_tool_button_delete_clicked), builder);

	g_signal_connect_after (GTK_NOTEBOOK (notebook), "switch-page", G_CALLBACK (on_switch_page), builder);
/* end of siganl & function */


	id = gtk_statusbar_get_context_id (GTK_STATUSBAR (builder->statusbar),
									  "Database Builder");
	builder->statusbar_context_id = id;
	set_statusbar (builder);
	set_sensitive(builder->si, FALSE);
	
	return TRUE;
}

