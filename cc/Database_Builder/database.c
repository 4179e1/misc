#include <gtk/gtk.h>
#include <sqlite3.h>
#include "database_builder.h"
#include "handler.h"
#include "tree.h"

#define NEW_ALIGNMENT "CREATE TABLE IF NOT EXISTS alignment (alignment TEXT PRIMARY KEY NOT NULL, description TEXT);"
#define LOAD_ALIGNMENT "SELECT * FROM ALIGNMENT;"

gboolean exec_sql (char *file, const char *sql)
{
	sqlite3 *db;
	char *err_msg;
	gint rc;
	/* open database */
	rc = sqlite3_open(file, &(db));

	/* if create fail */
	if( rc != SQLITE_OK) {
		error_message (sqlite3_errmsg (db));
		sqlite3_close(db);
		return FALSE;
	}

	rc = sqlite3_exec(db, sql, NULL, NULL, &err_msg);
	if (rc != SQLITE_OK)
	{
		error_message (err_msg);
		return FALSE;
	}

	sqlite3_close(db);

	return TRUE;
}

gboolean init_database(gchar *file)
{
	sqlite3 *db;
	char *err_msg;
	gint rc;
	/* open database */
	rc = sqlite3_open(file, &(db));

	/* if create fail */
	if( rc != SQLITE_OK) {
		error_message (sqlite3_errmsg (db));
		sqlite3_close(db);
		return FALSE;
	}

	g_print ("TODO: initial database\n");

	rc = sqlite3_exec(db, NEW_ALIGNMENT, NULL, NULL, &err_msg);
	if (rc != SQLITE_OK)
	{
		error_message (err_msg);
		return FALSE;
	}

	sqlite3_close(db);

	return TRUE;
}



static int callback_alignment(void *builder, int argc, char **argv, char **col_name)
{
	append_to_alignment ( ((DatabaseBuilder*)builder)->tree_view_alignment, argv[0], argv[1]);
	return 0;
}

gboolean load_alignment (DatabaseBuilder *builder)
{
	sqlite3 *db;
	char *err_msg;
	gint rc;
	/* open database */
	rc = sqlite3_open(builder->filename, &(db));

	/* if create fail */
	if( rc != SQLITE_OK) {
		error_message (sqlite3_errmsg (db));
		sqlite3_close(db);
		return FALSE;
	}



	rc = sqlite3_exec(db, LOAD_ALIGNMENT, callback_alignment, builder, &err_msg);
	if (rc != SQLITE_OK)
	{
		error_message (err_msg);
		return FALSE;
	}



	sqlite3_close(db);

	return TRUE;
}

void load_data (DatabaseBuilder *builder)
{
	load_alignment(builder);
}
