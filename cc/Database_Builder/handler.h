#ifndef _HANDLER_H_
#define _HANDLER_H_
gboolean check (const gchar *message);
void error_message (const gchar *message);
void set_statusbar (DatabaseBuilder *builder);
void set_sensitive (SensitiveItem *si, gboolean sensitive);

gboolean file_exists (const char *filename);
gboolean create_file (const char *filename);
gboolean copy_file (char *destination_file, char *source_file);
gboolean verify_database (char *filename);

#endif
