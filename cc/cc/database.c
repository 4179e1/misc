#include <gtk/gtk.h>
#include <sqlite3.h>
#include "comman.h"
#include "database.h"

gboolean create_database(DataBaseBuilder *dbb)
{
	//char *sql_error_msg;
	int rc;

	/* create database */
	rc = sqlite3_open(dbb->database_name_temp, &(dbb->db));

	/* if create fail */
	if( rc != SQLITE_OK) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(dbb->db));	
		sqlite3_close(dbb->db);
		return FALSE;
	} else {
		g_print("INFO: database %s create successfully\n", dbb->database_name_temp);
	}

	g_print("TODO: initialize database\n");

	sqlite3_close(dbb->db);
	/* what if dbb->title not long enough? */
	sprintf(dbb->title, "%s - %s", PROG_TITLE, dbb->database_name_temp );
	gtk_window_set_title(GTK_WINDOW(dbb->window), dbb->title);
	return TRUE;
}
