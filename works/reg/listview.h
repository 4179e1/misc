#ifndef _LISTVIEW_H
#define _LISTVIEW_H
GtkWidget* create_list_view_and_model (void);
void liststore_insert (GtkTreeView *treeview, const char *name, const char *type, const char *data);

#endif
