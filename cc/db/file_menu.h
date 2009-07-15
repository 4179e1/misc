#ifndef _FILE_MENU_H_
#define _FILE_MENU_H_
void on_file_wizard_activate(GtkMenuItem *menuitem, DataBaseBuilder *dbb);
void clear_data(DataBaseBuilder *dbb);
gboolean check_clear(DataBaseBuilder *dbb);
char *get_temp_filename(DataBaseBuilder *dbb);
void on_file_new_activate(GtkMenuItem *menuitem, DataBaseBuilder *dbb);
char *get_open_filename(DataBaseBuilder *dbb);
gboolean on_file_open_activate(GtkMenuItem *menuitem, DataBaseBuilder *dbb);
gboolean on_file_save_activate(GtkMenuItem *menuitem, DataBaseBuilder *dbb);
gboolean on_file_save_as_activate(GtkMenuItem *menuitem, DataBaseBuilder *dbb);
void on_file_quit_activate(GtkMenuItem *menuitem, DataBaseBuilder *dbb);
#endif
