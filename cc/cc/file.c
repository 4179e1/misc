#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "comman.h"
#include "menu.h"
#include "database.h"

#define DB_NAME_TEMP ".temp"
#define DB_NAME_SUFFIX ".db"


/*  File Menu */

/* File->Open */
/* detect which new filename for temporary datbase are available, /
   the file name is attached by DB_TEMP_NAME + count + DB_NAME_SUFFIX */
char *get_temp_filename(DataBaseBuilder *dbb)
{
	int count = 1;
	FILE *file = NULL;
	
	/* i don't know if it's nessary to allocate memory for a string, /
	 and what if i want to set filename to another string, do i need to free it first? */
	char *filename = (char *)malloc(sizeof(char) * MAX_LENGTH);
	assert(filename != NULL);

	g_print("TODO: if finename not long enough\n");
	
	/* generate the temporary file name */
	sprintf(filename, "%s%d%s", DB_NAME_TEMP, count, DB_NAME_SUFFIX);

	/* dectect file exist or not, if file don't exist, filename is available */
	for(; NULL != (file = fopen(filename, "r")); count++)
	{
		fclose(file);	//if file exist, colse it, generate next name
		sprintf(filename, "%s%d%s", DB_NAME_TEMP, count, DB_NAME_SUFFIX);
	}

	return filename;
}

void on_file_new_activate(GtkMenuItem *menuitem, DataBaseBuilder *dbb)
{
	/* clear current database */
	if(dbb->need_saved)
	{
		g_print("TODO: save unsaved file\n");
	}

	g_print("TODO: clear datalist\n");

	if(dbb->database_name_temp != NULL)
	{
		free(dbb->database_name_temp);
		g_print("DEBUG: freed memory\n");
	}

	/* get a usable temporary database name */
	dbb->database_name_temp = get_temp_filename(dbb);

	assert(dbb->database_name_temp != NULL);
	create_database(dbb);

}
