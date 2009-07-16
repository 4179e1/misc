#ifndef _LISTSTORE_H
#define _LISTSTORE_H
#include <gtk/gtk.h>

void liststore_insert (GtkTreeView *treeview, const char *protocol, const char *sip, const int sport, const char *dip, const int dport, const int size, const char *pdata);
GtkWidget* create_view_and_model (void);
void remove_tree_view(GtkTreeView *tree);
#endif
