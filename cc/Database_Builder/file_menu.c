#include <gtk/gtk.h>
#include "database_builder.h"
#include "file_menu.h"
#include "new_file.h"
#include "handler.h"
#include "database.h"
#include "tree.h"

static void load_file(DatabaseBuilder *builder);

void on_file_new_activate(GtkMenuItem *menuitem, DatabaseBuilder *builder)
{
	gchar *filename = open_file(builder);
	if (filename != NULL)
	{
		on_file_close_activate(NULL, builder);
		builder->filename = filename;
		load_file(builder);
	}
}

static gchar *get_open_filename (void)
{
	GtkWidget *chooser;
	gchar *filename = NULL;

	chooser = gtk_file_chooser_dialog_new ("Open File...",
			NULL,
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

void on_file_open_activate (GtkMenuItem *menuitem, DatabaseBuilder *builder)
{
	gchar *filename = get_open_filename();

	if (NULL == filename)
	{
		return;
	}

	if (!verify_database(filename))
	{
		error_message ("Error: Not a vaild database file!");
		return;
	}

	on_file_close_activate(NULL, builder);
	builder->filename = filename;
	load_file(builder);
}

void on_file_close_activate(GtkMenuItem *menuitem, DatabaseBuilder *builder)
{
	if(builder->filename != NULL)
	{
		g_free(builder->filename);
		builder->filename = NULL;
		builder->database = NULL;

		g_print("TODO: clear tree view\n");
		remove_tree_view (GTK_TREE_VIEW (builder->tree_view_alignment));

		set_statusbar (builder);
		set_sensitive (builder->si, FALSE);
	}
}

void on_file_quit_activate (GtkMenuItem *menuitem, DatabaseBuilder *builder)
{
	on_file_close_activate (NULL, builder);
	gtk_main_quit();
}

static void load_file(DatabaseBuilder *builder)
{
	if (!verify_database(builder->filename))
	{
		error_message ("Error: Not a vaild database file!");
		return;
	}

	gint rc;
	/* open database */
	rc = sqlite3_open(builder->filename, &(builder->database));

	/* if create fail */
	if( rc != SQLITE_OK) {
		error_message (sqlite3_errmsg (builder->database));
		sqlite3_close(builder->database);
		return;
	}

	g_print ("TODO: load tree view\n");
	load_data(builder);

	sqlite3_close(builder->database);
	
	set_statusbar (builder);
	set_sensitive (builder->si, TRUE);
}
