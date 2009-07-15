#ifndef _FILE_MENU_H_
#define _FILE_MENU_H_
void on_file_new_activate (GtkMenuItem *menuitem, DatabaseBuilder *builder);
void on_file_open_activate (GtkMenuItem *menuitem, DatabaseBuilder *builder);
void on_file_close_activate (GtkMenuItem *menuitem, DatabaseBuilder *builder);
void on_file_quit_activate (GtkMenuItem *menuitem, DatabaseBuilder *builder);

#endif
