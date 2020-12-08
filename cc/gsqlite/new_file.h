#ifndef _NEW_FILE_H_
#define _NEW_FILE_H_

typedef struct
{
	GtkWidget	*new_file_window;
	GtkWidget	*check_button_source;
	GtkWidget	*entry_name;
	GtkWidget	*check_button_location;
	GtkWidget	*entry_location;
	GtkWidget	*button_browse;
	GtkWidget	*button_cancel;
	GtkWidget	*button_save;

	gchar		*filename;

	gboolean	default_source;
} NewFileWindow;

gchar *open_file (DatabaseBuilder *builder);
gchar *get_filename(DatabaseBuilder *builder);
void on_entry_name_changed (GtkEditable *entry_name, NewFileWindow *nf);
void on_check_button_location_clicked (GtkButton *button_location, NewFileWindow *nf);
void on_button_browse_clicked (GtkButton *button_browse, NewFileWindow *nf);
void on_button_cancel_clicked (GtkButton *button_cancel, NewFileWindow *nf);
void on_button_save_clicked (GtkButton *button_save, NewFileWindow *nf);

gchar *get_location(NewFileWindow *nf);

#endif
