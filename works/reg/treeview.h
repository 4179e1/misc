#ifndef _TREEVIEW_H
#define _TREEVIEW_H
GtkWidget* create_tree_view_and_model (void);
void on_tree_view_row_activated (GtkTreeView *view, GtkTreePath *path, GtkTreeViewColumn *col, Reg *reg);
void treestore_insert (Reg *reg, const char *str);
void remove_tree_view(GtkTreeView *tree);

#endif
