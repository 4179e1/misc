#ifndef _EDIT_MENU_H_
#define _EDIT_MENU_H_
void on_switch_page (GtkNotebook *notebook, GtkNotebookPage *page, guint page_num, DatabaseBuilder *builder);
void on_edit_add_activate(GtkMenuItem *menuitem, DatabaseBuilder *builder);
void on_edit_edit_activate(GtkMenuItem *menuitem, DatabaseBuilder *builder);
void on_edit_delete_activate(GtkMenuItem *menuitem, DatabaseBuilder *builder);

void add_to_alignment(DatabaseBuilder *builder, gboolean edit);

#endif
