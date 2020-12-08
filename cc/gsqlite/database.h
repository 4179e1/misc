#ifndef _DATABASE_H_
#define _DATABASE_H_
gboolean exec_sql (char *file, const char *sql);
gboolean init_database (gchar *file);
gboolean load_alignment (DatabaseBuilder *builder);
void load_data (DatabaseBuilder *builder);

#endif
