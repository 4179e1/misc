#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "comman.h"
#include "signal.h"
#include "file_menu.h"
#include "dbb.h"
#include "database.h"

#define DB_NAME_TEMP ".temp"
#define DB_NAME_SUFFIX ".db"

/* copy source file to destination file */
#define BUFFER_SIZE 1024
gboolean write_file(char *destination_file, char *source_file)
{
	g_print("INFO: write_file\n");

	char *buffer[BUFFER_SIZE];
	FILE *dfp;
	FILE *sfp;

	/* the number of bytes read from source file */
	int num_read;

	if( NULL == (sfp = fopen(source_file, "rb")))
	{
		g_print("ERROR: cannot open file: %s\n", source_file);
		return FALSE;
	}
	if( NULL == (dfp = fopen(destination_file, "wb")))
	{
		g_print("ERROR: cannot write file: %s\n", destination_file);
		return FALSE;
	}

	while (feof(sfp) == 0)
	{
		num_read = fread (buffer, 1, BUFFER_SIZE, sfp);
		fwrite (buffer, 1, num_read, dfp);
	}

	g_print("INFO: copy file from %s to %s successful\n", source_file, destination_file);

	fclose(sfp);
	fclose(dfp);

	return TRUE;
}

void clear_data(DataBaseBuilder *dbb)
{
	g_print("INFO: clear_data\n");

	/* new_db may have been changed during save, so it need to check again */
	if(dbb->new_db)
	{
		/* temporary database should be delete, no mattar it need to save or not /
		 if file need to save , it has been copy to a new file or operation canceled 
		 if don't, the file dosen't have any datas */
		remove(dbb->database_name);
		g_print("INFO: Clear_Data: %s deletede\n", dbb->database_name);
	}

	free(dbb->database_name);

	g_print("TODO: clear tree view \n");
	g_print("INFO: data cleared\n");

	return;

}

/* clear files in the window, while opening or creating a new file */
/* return TRUE if datas clears, FALSE if not or canceled */
gboolean check_clear(DataBaseBuilder *dbb)
{
	g_print("INFO: clear data\n");
	/* clear current database */
	if(dbb->new_db)
	{
		if(dbb->need_saved) 
		{
			int result = check_for_save(dbb);

			switch(result)
			{
				case GTK_RESPONSE_YES:	
					g_print("INFO: YES selected, save database\n");
					if(!on_file_save_activate(NULL, dbb))	// if select to save a file but clicked cancel in the save file dialog
					{
						return FALSE;
					}
					break;
				case GTK_RESPONSE_NO:
					g_print("INFO: NO selected, don't save\n");
					break;
				case GTK_RESPONSE_CANCEL:
					g_print("INFO: CANCEL selected, do nothing\n");
					return FALSE;
					break;
				default:
					break;
			}

		}


	}

	return TRUE;
}


/* File->Wizard */
void on_file_wizard_activate(GtkMenuItem *menuitem, DataBaseBuilder *dbb)
{
	g_print("INFO: File->Wizard\n");
	start(dbb);
}

/* File->New */
/* detect which new filename for temporary datbase are available, /
   the file name is attached by DB_TEMP_NAME + count + DB_NAME_SUFFIX */
char *get_temp_filename(DataBaseBuilder *dbb)
{
	g_print("INFO: get_temp_filename\n");
	int count = 1;
	FILE *file = NULL;
//	char *filename;

//	filename = (char *)malloc(sizeof(char)*MAX_LENGTH);	
	char filename[MAX_LENGTH];

	g_print("TODO: if finename not long enough\n");
	/* generate the temporary file name */
	/* In theory, filename can to too long to put it in the string /
	 however, most of time, it should be enough */
	sprintf(filename, "%s%d%s", DB_NAME_TEMP, count, DB_NAME_SUFFIX);

	/* dectect file exist or not, if file don't exist, filename is available */
	for(; (file = fopen(filename, "r")) != NULL; count++)
	{
		fclose(file);	//if file exist, colse it, generate next name
		sprintf(filename, "%s%d%s", DB_NAME_TEMP, count, DB_NAME_SUFFIX);
	}

	return filename;
}

void on_file_new_activate(GtkMenuItem *menuitem, DataBaseBuilder *dbb)
{
	g_print("INFO: File->New\n");

	/* if data not clear, cancel operation */
	if(!check_clear(dbb))
		return;
	clear_data(dbb);

	/* get a usable temporary database name */
	dbb->database_name = get_temp_filename(dbb);

	assert(dbb->database_name != NULL);
	create_database(dbb);
	g_print("TODO: initial database\n");
	dbb->new_db = TRUE;
	dbb->need_saved = FALSE;
}


/* File->Open */

//static char *open_filename = NULL;

char *get_open_filename (DataBaseBuilder *dbb)
{
	g_print("INFO: get_open_filename\n");
	GtkWidget *chooser;
	char *filename = NULL;

	chooser = gtk_file_chooser_dialog_new ("Open File...",
			GTK_WINDOW(dbb->window),
			GTK_FILE_CHOOSER_ACTION_OPEN,
			GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
			GTK_STOCK_OPEN, GTK_RESPONSE_OK,
			NULL);

	if (GTK_RESPONSE_OK == (gtk_dialog_run ( GTK_DIALOG (chooser))))
	{
		filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (chooser));
	}
	gtk_widget_destroy (chooser);
	return filename;
}

/* this is the file header of a sqlite3 database */
#define HDR_SIZE 16
#define SQLITE_HDR 0x53, 0x51, 0x4c, 0x69, 0x74, 0x65, 0x20, 0x66, 0x6f, 0x72, 0x6d, 0x61, 0x74, 0x20, 0x33, 0x00
gboolean verify_database(char *filename)
{
	g_print("INFO: verify_database\n");
	FILE *file;
	int num_read;
	char *buffer = (char *) malloc (sizeof(char)*HDR_SIZE);

	char header[] = {SQLITE_HDR};


	if ( NULL == (file = fopen(filename, "r")))
	{
		fprintf(stderr, "ERROR: file %s cannot open\n", filename);
		return FALSE;
	}

	num_read = fread(buffer, 1, HDR_SIZE, file);

	if ( 0 == num_read )
	{
		g_print("INFO: empty file, accept\n");
		return TRUE;
	}
	else
	{
		if (0 == memcmp (buffer, header, HDR_SIZE))
		{
			g_print("INFO: valid database file, accept\n");
			return TRUE;
		}
		else
		{
			g_print("INFO: not a database file, reject\n");
			return FALSE;
		}
	}

	assert(FALSE);
	return FALSE;
}

/* return TRUE if file opened, FALSE if not a database file or cancled */
gboolean on_file_open_activate(GtkMenuItem *menuitem, DataBaseBuilder *dbb)
{

	char *filename;

	g_print("INFO :File->Open\n");

	filename = get_open_filename(dbb);

	/* CANCEL seleted in open file dialog */
	if(NULL == filename)	
		return FALSE;

	if(verify_database(filename))
	{
		if(!check_clear(dbb))
				return FALSE;
		clear_data(dbb);
		dbb->database_name = filename;
		create_database(dbb);
		dbb->new_db = FALSE;
		return TRUE;
	}
	else
	{
		g_print("TODO: MESSAGE: not valid file\n");
		show_message(dbb, "Not a vaild database file!");
		return FALSE;
	}

}


/* File->Save */
/* an existed file don't need to save, it always return TURE /
 to a new file, return TURE if saved, FALSE if not */
gboolean on_file_save_activate(GtkMenuItem *menuitem, DataBaseBuilder *dbb)
{
	g_print("INFO: File->Save\n");
	/* only a new temporary database need to save /
	 exactly speaking, it copye the temp file to user named file */
	/* an exist databse don't need to save, 
	   because each time you success to execute an sql statment,
	 the changes has been saved to database */
	if(dbb->new_db)
		return(on_file_save_as_activate(NULL, dbb));
	else
	{
		g_print("TODO: STATUSBAR: don't need to save\n");
		return TRUE;
	}

	assert(FALSE);
	return FALSE;
}


/* File->Save as */
/* show up a file chooser dialog to get filename */
char *get_save_filename (DataBaseBuilder *dbb)
{
	g_print("INFO: get_save_filename\n");
	GtkWidget *chooser;
	char *filename = NULL;

	chooser = gtk_file_chooser_dialog_new ("Save File...",
			GTK_WINDOW(dbb->window),
			GTK_FILE_CHOOSER_ACTION_SAVE,
			GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
			GTK_STOCK_SAVE, GTK_RESPONSE_OK,
			NULL);

	if (GTK_RESPONSE_OK == (gtk_dialog_run ( GTK_DIALOG (chooser))))
	{
		filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (chooser));
	}
	gtk_widget_destroy (chooser);
	return filename;
}

/* return TRUE if file saved , FALSE if not saved or error */
gboolean on_file_save_as_activate(GtkMenuItem *menuitem, DataBaseBuilder *dbb)
{
	g_print("INFO: File->Save as\n");
	char *filename = NULL;

	filename = get_save_filename(dbb);

	if (NULL == filename)
	{
		g_print("INFO: no filename given, abort\n");
		return FALSE;
	}
	else
	{
		if (write_file(filename, dbb->database_name))
		{
			/* dbb->new_db should be set before clear_data(), if status changed */
			dbb->new_db = FALSE;
			if(!check_clear(dbb))
			{	
				g_print("INFO: not cleared, return\n");
				return FALSE;
			}
			remove(dbb->database_name);
			g_print("INFO: File-Save: %s deleted\n", dbb->database_name);
			clear_data(dbb);
			dbb->database_name = filename;
			create_database(dbb);			
			return TRUE;
		}
		else
		{
			show_message(dbb, "Error, can't access file!");
			return FALSE;
		}
	}

}

/* File->Quit */
void on_file_quit_activate(GtkMenuItem *menuitem, DataBaseBuilder *dbb)
{
	g_print("INFO: File->Quit\n");
	on_window_delete_event(dbb->window, NULL, dbb);
}
