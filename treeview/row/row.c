
void onTreeViewRowActivated (GtkTreeView *view; GtkTreePath *path, GtkTreeViewColumn *col, gpointer userdata) {
	GtkTreeIter iter;
	GtkTreeModel *model;

	model = gtk_tree_view_get_model (view);

	if (gtk_tree_model_get_iter (model, &iter, path))
	{
		gchar *name;

		gtk_tree_model_get (model, &iter, COL_NAME, &name, -1);

		g_print ("The row containing the name '%s' has been double-clicked.\n", name);

		g_free (name);
	}
}
