#ifndef _DEBUG_MENU_H_
#define _DEBUG_MENU_H_
void on_debug_clear_database_activate(GtkMenuItem *menuitem, DataBaseBuilder *dbb);
static int callback(void *unused, int argc, char **argv, char **col_name);
void on_button_clicked(GtkButton *button, DataBaseBuilder *dbb);
void on_debug_exec_sql_command_activate(GtkMenuItem *menuitem, DataBaseBuilder *dbb);
#endif
