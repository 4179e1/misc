#ifndef _SIGNAL_H_
#define _SIGNAL_H_
void show_message(DataBaseBuilder *dbb, char *message);
int check_for_save(DataBaseBuilder *dbb);
gboolean on_window_delete_event(GtkWidget *window, GdkEvent *event, DataBaseBuilder *dbb);
void on_tool_button_add_clicked(GtkButton *button, DataBaseBuilder *dbb);
void on_tool_button_edit_clicked(GtkButton *button, DataBaseBuilder *dbb);
void on_tool_button_delete_clicked(GtkButton *button, DataBaseBuilder *dbb);
#endif
