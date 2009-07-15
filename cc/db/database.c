#include <gtk/gtk.h>
#include <sqlite3.h>
#include "comman.h"
#include "database.h"

/* create a new database or open a existed one */
gboolean create_database(DataBaseBuilder *dbb)
{
	//char *sql_error_msg;
	int rc;

	/* create database */
	rc = sqlite3_open(dbb->database_name, &(dbb->db));

	/* if create fail */
	if( rc != SQLITE_OK) {
		fprintf(stderr, "ERROR: Can't open database: %s\n", sqlite3_errmsg(dbb->db));	
		sqlite3_close(dbb->db);
		return FALSE;
	} else {
		g_print("INFO: database %s open successfully\n", dbb->database_name);
	}

	sqlite3_close(dbb->db);
	/* what if dbb->title not long enough? */
	sprintf(dbb->title, "%s - %s", PROG_TITLE, dbb->database_name );
	gtk_window_set_title(GTK_WINDOW(dbb->window), dbb->title);
	return TRUE;
}
