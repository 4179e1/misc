#if 0
gcc -Wall -O2 -o main main.c `pkg-config --libs --cflags gtk+-2.0`
exit
#endif

#include <gtk/gtk.h>

#define ARRAY_SIZE(A)	(sizeof(A) / sizeof (A[0]))

gchar *abc[] = 
{
	"title 1",
	"a---",
	"b---",
	"c---",
	NULL,
};

gchar *def[] = 
{
	"title 2",
	"d---",
	"e---",
	"f---",
	NULL,
};

gchar **list[] = 
{
	abc,
	def,
};

GtkTreeModel *model_new (void)
{
	GtkTreeIter iter, iter2;
	gint i;

	GtkTreeStore *store = gtk_tree_store_new (1, G_TYPE_STRING);
	for (i = 0; i < ARRAY_SIZE(list); i++)
	{
		gtk_tree_store_append (store, &iter, NULL);
		gtk_tree_store_set (store, &iter, 0, list[i][0],-1);

		gchar **str = &(list[i][1]);
		for (; *str != NULL; str++)
		{
			gtk_tree_store_append (store, &iter2, &iter);
			gtk_tree_store_set (store, &iter2, 0, *str, -1);
		}
	}

	return GTK_TREE_MODEL (store);
}

static void is_capital_sensitive (GtkCellLayout   *cell_layout,
		GtkCellRenderer *cell,
		GtkTreeModel    *tree_model,
		GtkTreeIter     *iter,
		gpointer         data)
{
	gboolean sensitive;

	sensitive = !gtk_tree_model_iter_has_child (tree_model, iter);

	g_object_set (cell, "sensitive", sensitive, NULL);
}

int main (int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *box;
	GtkWidget *combo;
	GtkCellRenderer *renderer;

	gtk_init (&argc, &argv);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit), (gpointer)window);

	box = gtk_vbox_new (FALSE, 2);
	gtk_container_add (GTK_CONTAINER (window), box);

	GtkTreeModel *model = model_new();

	combo = gtk_combo_box_entry_new ();
	gtk_combo_box_set_model (GTK_COMBO_BOX (combo), model);
	gtk_combo_box_entry_set_text_column (GTK_COMBO_BOX_ENTRY (combo), 0);
	gtk_box_pack_start_defaults (GTK_BOX (box), combo);


	GtkWidget *c = gtk_combo_box_new();
	renderer = gtk_cell_renderer_text_new ();
	gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (c), renderer, TRUE);
	gtk_cell_layout_set_attributes (GTK_CELL_LAYOUT (c), renderer, "text", 0, NULL);
	gtk_combo_box_set_model (GTK_COMBO_BOX (c), model);
	gtk_box_pack_start_defaults (GTK_BOX (box), c);
	gtk_cell_layout_set_cell_data_func (GTK_CELL_LAYOUT (c),
			renderer,
			is_capital_sensitive,
			NULL, NULL);

	gtk_widget_show_all (window);

	gtk_main ();

	return 0;
}
