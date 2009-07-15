#ifndef _TREE_H_
#define _TREE_H_
void remove_tree_view(GtkTreeView *tree);
void remove_item(GtkWidget *tree, GtkTreeSelection *selection);
void init_alignment (GtkWidget *alignment);
void append_to_alignment (GtkWidget *alignment, const gchar *str, const gchar *str2);

#endif
