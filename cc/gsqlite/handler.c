#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database_builder.h"
#include "handler.h"

#define BUFFER_SIZE 1024

/* this is the file header of sqlite3 database, the size is 32 byte , that is 16 char */
#define HDR_SIZE 16
#define SQLITE_HDR 0x53, 0x51, 0x4c, 0x69, 0x74, 0x65, 0x20, 0x66, 0x6f, 0x72, 0x6d, 0x61, 0x74, 0x20, 0x33, 0x00

gboolean check (const gchar *message)
{
	GtkWidget	*dialog;
	gboolean	result = FALSE;

	dialog = gtk_message_dialog_new (NULL,
									 GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
									 GTK_MESSAGE_QUESTION,
									 GTK_BUTTONS_YES_NO,
									 message);
	gtk_window_set_title (GTK_WINDOW (dialog), "Question...");
	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_YES)
	{
		result = TRUE;
	}
	else
	{
		result = FALSE;
	}

	gtk_widget_destroy (dialog);

	return result;
}

/*
We call error_message() any time we want to display an error message to the
user. It will both show an error dialog and log the error to the terminal
window.
*/
void error_message (const gchar *message)
{
	GtkWidget *dialog;

	/* log to terminal window */
	g_warning (message);

	/* create an error message dialog and display modally to user */
	dialog = gtk_message_dialog_new (NULL,
									 GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
									 GTK_MESSAGE_ERROR,
									 GTK_BUTTONS_OK,
									 message);

	gtk_window_set_title (GTK_WINDOW (dialog), "Error!");
	gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (dialog);
}

/*
We call set_statusbar() when we want to remove the last default status
and set it again based on the current file. 
*/
void set_statusbar (DatabaseBuilder *builder)
{
	gchar	*file;
	gchar 	*status;
	
	if (NULL == builder->filename)
	{
		file = g_strdup ("(NULL)");
	}
	else file = g_path_get_basename (builder->filename);

	status = g_strdup_printf ("Database: %s", file);
	gtk_statusbar_pop (GTK_STATUSBAR (builder->statusbar),
					   builder->statusbar_context_id);
	gtk_statusbar_push (GTK_STATUSBAR (builder->statusbar),
						builder->statusbar_context_id, status);

	g_free (status);
	g_free (file);

}

void set_sensitive (SensitiveItem *si, gboolean sensitive)
{
	gtk_widget_set_sensitive (si->edit_add, sensitive);
	gtk_widget_set_sensitive (si->edit_edit, sensitive);
	gtk_widget_set_sensitive (si->edit_delete, sensitive);
	gtk_widget_set_sensitive (si->debug_exec_sql_command, sensitive);
	gtk_widget_set_sensitive (si->file_close, sensitive);
	gtk_widget_set_sensitive (GTK_WIDGET (si->tool_button_add), sensitive);
	gtk_widget_set_sensitive (GTK_WIDGET (si->tool_button_edit), sensitive);
	gtk_widget_set_sensitive (GTK_WIDGET (si->tool_button_delete), sensitive);
}

gboolean file_exists(const char * filename)
{
	FILE *file = fopen(filename, "r");

    if (NULL != file)
    {
        fclose(file);
        return TRUE;
    }

    return FALSE;
}

gboolean create_file(const char *filename)
{
	FILE *file = fopen(filename, "w");

	if (NULL != file)
	{
		fclose(file);
		return TRUE;
	}

	return FALSE;
}

gboolean copy_file (char *destination_file, char *source_file)
{
	char *buffer[BUFFER_SIZE];
	FILE *dfp;
	FILE *sfp;

	/* the number of bytes read from source file */
	int num_read;

	if( NULL == (sfp = fopen(source_file, "rb")))
	{
		error_message ("ERROR: cannot open source file\n");
		return FALSE;
	}
	if( NULL == (dfp = fopen(destination_file, "wb")))
	{
		error_message ("ERROR: cannot write destination file\n");
		return FALSE;
	}

	while (feof(sfp) == 0)
	{
		num_read = fread (buffer, 1, BUFFER_SIZE, sfp);
		fwrite (buffer, 1, num_read, dfp);
	}

	fclose(sfp);
	fclose(dfp);

	return TRUE;
}

gboolean verify_database(char *filename)
{
	FILE *file;
	int num_read;
//	char *buffer = (char *) malloc (sizeof(char)*HDR_SIZE);
	char buffer[HDR_SIZE];

	char header[] = {SQLITE_HDR};


	if ( NULL == (file = fopen(filename, "r")))
	{
		error_message ("ERROR: cannot verify file, file doesn't exist or cannot access\n");
		return FALSE;
	}

	num_read = fread(buffer, 1, HDR_SIZE, file);

	if ( 0 == num_read )
	{
		g_print("INFO: empty file, accept\n");
		return TRUE;
	}

	if (0 == memcmp (buffer, header, HDR_SIZE))
	{
//		g_print("INFO: valid database file, accept\n");
		return TRUE;
	}
	else
	{
//		g_print("INFO: not a database file, reject\n");
		return FALSE;
	}

//	free (buffer);
}
