#ifndef _DBB_H_
#define _DBB_H_
void 		init_data(DataBaseBuilder *dbb);
gboolean 	init_gui(DataBaseBuilder *dbb);
gboolean	on_start_window_delete_event(GtkWidget *window, GdkEvent *event,DataBaseBuilder *dbb);
void		on_button_cancle_clicked(GtkButton *button_cancel, DataBaseBuilder *dbb);
void		on_button_ok_clicked(GtkButton *button_ok, DataBaseBuilder *dbb);
void		start(DataBaseBuilder *dbb);

#endif
