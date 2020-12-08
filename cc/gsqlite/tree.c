#include <gtk/gtk.h>
#include "database_builder.h"
#include "tree.h"

void remove_tree_view(GtkTreeView *tree)
{
	GtkListStore *store;
	GtkTreeModel *model;
	GtkTreeIter iter;
	
	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(tree)));
	model = gtk_tree_view_get_model(GTK_TREE_VIEW(tree));
	
	if (gtk_tree_model_get_iter_first(model, &iter) == FALSE)
		return;

	gtk_list_store_clear(store);
}

void remove_item(GtkWidget *tree, GtkTreeSelection *selection)
{
	GtkListStore *store;
	GtkTreeModel *model;
	GtkTreeIter iter;

	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(tree)));
	model = gtk_tree_view_get_model(GTK_TREE_VIEW(tree));

	if(gtk_tree_model_get_iter_first(model, &iter) == FALSE)
		return;
	
	if(gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), &model, &iter)) {
		gtk_list_store_remove(GTK_LIST_STORE (model), &iter);
	}
}

enum
{
	ALIGNMENT_ALIGNMENT = 0,
	ALIGNMENT_DESCRIPTION,
	ALIGNMENT_N
};

void init_alignment (GtkWidget *list)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkListStore *store;

	store = gtk_list_store_new(ALIGNMENT_N, G_TYPE_STRING, G_TYPE_STRING);
	gtk_tree_view_set_model(GTK_TREE_VIEW(list), GTK_TREE_MODEL(store));
	g_object_unref(store);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Alignment",
			renderer,
			"text", ALIGNMENT_ALIGNMENT,
			NULL);
	gtk_tree_view_column_set_sort_column_id (column, ALIGNMENT_ALIGNMENT);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

	column = gtk_tree_view_column_new_with_attributes("Description",
			renderer,
			"text", ALIGNMENT_DESCRIPTION,
			NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

}

void append_to_alignment (GtkWidget *alignment, const gchar *str, const gchar *str2)
{
	GtkListStore *store;
	GtkTreeIter iter;

	store = GTK_LIST_STORE (gtk_tree_view_get_model (GTK_TREE_VIEW (alignment)));

	gtk_list_store_append(store, &iter);
	gtk_list_store_set(store, &iter,
			ALIGNMENT_ALIGNMENT, str,
			ALIGNMENT_DESCRIPTION, str2,
			-1);
}
