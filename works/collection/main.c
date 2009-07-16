#include <gtk/gtk.h>
#include <stdlib.h>
#include "collection.h"
#include "callback.h"
#include "scan.h"

enum
{
	COLUMN = 0,
	NUM_COLS 
};

static char *list[] = {
	"获取主机IP地址、子网掩码和计算机名",
	"获取域名服务器、子网掩码",
	"获取网卡类型、网卡MAC地址",
	"端口扫描",
	NULL
};

void on_changed (GtkWidget *widget, Collection *collection) 
{
  GtkTreeIter iter;
  GtkTreeModel *model;
  char *value;


  if (gtk_tree_selection_get_selected(
      GTK_TREE_SELECTION(widget), &model, &iter)) {

    gtk_tree_model_get(model, &iter, COLUMN, &value,  -1);
    gtk_statusbar_push(GTK_STATUSBAR(collection->statusbar), gtk_statusbar_get_context_id(GTK_STATUSBAR(collection->statusbar), value), value);

	if (g_strcmp0 (value, list[0]) == 0) {
		acquire_ip (collection);
	} else if (g_strcmp0 (value, list[1]) == 0) {
		acquire_dns (collection);
	} else if (g_strcmp0 (value, list[2]) == 0) {
		acquire_adapter (collection);
	} else if (g_strcmp0 (value, list[3]) == 0) {
		to_scan (collection);
	}

    g_free(value);
  }
}

static GtkTreeModel *
create_and_fill_model (void)
{
  GtkTreeStore *treestore;
  GtkTreeIter toplevel, child;
  char **lp;

  treestore = gtk_tree_store_new(NUM_COLS,
                  G_TYPE_STRING);

  gtk_tree_store_append(treestore, &toplevel, NULL);
  gtk_tree_store_set(treestore, &toplevel,
                     COLUMN, "基本网络应用汇总",
                     -1);

  for ( lp = list; *lp != NULL; lp ++)
  {
	  gtk_tree_store_append(treestore, &child, &toplevel);
	  gtk_tree_store_set(treestore, &child,
                     COLUMN, *lp,
                     -1);
  }

  return GTK_TREE_MODEL(treestore);
}


static GtkWidget *
create_view_and_model (void)
{
  GtkTreeViewColumn *col;
  GtkCellRenderer *renderer;
  GtkWidget *view;
  GtkTreeModel *model;

  view = gtk_tree_view_new();
  gtk_tree_view_set_headers_visible (GTK_TREE_VIEW (view), FALSE);

  col = gtk_tree_view_column_new();
  gtk_tree_view_append_column(GTK_TREE_VIEW(view), col);

  renderer = gtk_cell_renderer_text_new();
  gtk_tree_view_column_pack_start(col, renderer, TRUE);
  gtk_tree_view_column_add_attribute(col, renderer, 
      "text", COLUMN);

  model = create_and_fill_model();
  gtk_tree_view_set_model(GTK_TREE_VIEW(view), model);
  g_object_unref(model); 

  return view;
}

int main(int argc, char *argv[])
{
	Collection *collection;

	collection = g_slice_new (Collection);
	if (collection == NULL)
	{
		fprintf (stderr, "Error: not enought space\n");
		exit (1);
	}

	GtkWidget *window;
	GtkWidget *menubar;
	GtkWidget *hpaned;
	GtkWidget *treeview;
	GtkWidget *textview;
	GtkWidget *vbox;
	GtkWidget *statusbar;

	GtkTreeSelection *selection;

	GtkWidget *file;
	GtkWidget *view;
	GtkWidget *help;

	GtkWidget *filemenu;
	GtkWidget *file_quit;

	GtkWidget *viewmenu;
	GtkWidget *view_statusbar;

	GtkWidget *helpmenu;
	GtkWidget *help_about;

	gtk_init (&argc, &argv);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "基本网络应用汇总");
	gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size (GTK_WINDOW (window), 600, 400);

	vbox = gtk_vbox_new (FALSE, 0);
	gtk_container_add (GTK_CONTAINER (window), vbox);

	menubar = gtk_menu_bar_new();
	gtk_box_pack_start (GTK_BOX (vbox), menubar, FALSE, FALSE, 0);

	hpaned = gtk_hpaned_new ();
	gtk_box_pack_start (GTK_BOX (vbox), hpaned, TRUE, TRUE, 0);

	//treeview = gtk_tree_view_new ();
	treeview = create_view_and_model();
	gtk_paned_add1 (GTK_PANED (hpaned), treeview);

	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (treeview));

	textview = gtk_text_view_new ();
	gtk_paned_add2 (GTK_PANED (hpaned), textview);

	statusbar = gtk_statusbar_new();
	gtk_box_pack_start (GTK_BOX (vbox), statusbar, FALSE, FALSE, 0);

	file = gtk_menu_item_new_with_mnemonic ("_File");
	view = gtk_menu_item_new_with_mnemonic ("_View");
	help = gtk_menu_item_new_with_mnemonic ("_Help");
	gtk_menu_shell_append (GTK_MENU_SHELL (menubar), file);
	gtk_menu_shell_append (GTK_MENU_SHELL (menubar), view);
	gtk_menu_shell_append (GTK_MENU_SHELL (menubar), help);

	filemenu = gtk_menu_new();
	viewmenu = gtk_menu_new();
	helpmenu = gtk_menu_new();
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (file), filemenu);
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (view), viewmenu);
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (help), helpmenu);

	file_quit = gtk_image_menu_item_new_from_stock (GTK_STOCK_QUIT, NULL);
	gtk_menu_shell_append (GTK_MENU_SHELL (filemenu), file_quit);

	view_statusbar =gtk_check_menu_item_new_with_label ("Statusbar");
	gtk_menu_shell_append (GTK_MENU_SHELL (viewmenu), view_statusbar);

	help_about = gtk_image_menu_item_new_from_stock (GTK_STOCK_ABOUT, NULL);
	gtk_menu_shell_append (GTK_MENU_SHELL (helpmenu), help_about);

	collection->window = window;
	collection->statusbar = statusbar;
	collection->textview = textview;

	gtk_widget_show_all (window);

	g_signal_connect_swapped (G_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit), G_OBJECT (window));

	g_signal_connect (selection, "changed", G_CALLBACK (on_changed), collection);

	gtk_main();

	g_slice_free (Collection, collection);

	return 0;
}
