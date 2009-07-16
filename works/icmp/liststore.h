#ifndef _LISTSTORE_H
#define _LISTSTORE_H
#include <gtk/gtk.h>

void liststore_insert (GtkTreeView *treeview, const int id, const int time, const char *ip, const char *msg);
GtkWidget* create_view_and_model (void);
void remove_tree_view(GtkTreeView *tree);
#endif
