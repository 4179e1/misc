#ifndef _STRUCT_H_
#define _STRUCT_H_
#include <sqlite3.h>
typedef struct
{
	GtkWidget *window;
	GtkWidget *statusbar;

	char *title;

	sqlite3 *db;

	char *database_name;
	char *database_name_temp;
	gboolean need_saved;
} DataBaseBuilder;

#define PROG_TITLE "Database Builder"
#define MAX_LENGTH 256

#endif
