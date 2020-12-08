#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "database_builder.h"
#include "debug_menu.h"

#define SQL_SH "sqlite> "
#define MAX_SQL_STATMENT_LENGTH 1024

static void on_button_clicked(GtkButton *button, DatabaseBuilder *builder);
static void on_button_clicked(GtkButton *button, DatabaseBuilder *builder);
static gboolean on_command_window_delete_event (GtkWidget *command_window, GdkEvent *event, sqlite3 *database);


/* Debug->Exec sql command */
static GtkTextIter iter;
static gboolean col_name_printed;

static GtkTextBuffer *buffer;
static GtkWidget *entry;

/* according the numbers of rows that sqlite return,
   callback func will run exactly the number of times */
static int callback(void *unused, int argc, char **argv, char **col_name)
{
	int col_num;

	/* print the column name, it will be printed only once */
	if(!col_name_printed)
	{
		for(col_num=0; col_num < argc; col_num++)
		{
			gtk_text_buffer_insert(buffer, &iter, col_name[col_num], -1 );
			gtk_text_buffer_insert(buffer, &iter, "\t", -1);
		}
		gtk_text_buffer_insert(buffer, &iter, "\n", -1);
		col_name_printed = TRUE;
	}
	
	/* print column values; */
	for(col_num=0; col_num < argc; col_num++)
	{
		gtk_text_buffer_insert(buffer, &iter, (argv[col_num] ? argv[col_num] : "NULL"), -1 );
		gtk_text_buffer_insert(buffer, &iter, "\t", -1);
	}

	gtk_text_buffer_insert(buffer, &iter, "\n", -1);
	printf("\n");
  	return 0;
}

static void on_button_clicked(GtkButton *button, DatabaseBuilder *builder)
{
	gint rc;
	gchar *err_msg;
	const gchar *sql_statment;
	gchar *sql_statment_checked;
	gint sql_statment_length;

	col_name_printed = FALSE;
	
	/* gcc would give a waring if sql_statment is NOT a const string */
	sql_statment = gtk_entry_get_text(GTK_ENTRY(entry));

	sql_statment_length = strlen(sql_statment);

	/* if sql statment is NULL, return */
	if( 0 == sql_statment_length )
	{
		g_print("DEBUG: NULL string\n");
		return;
	}
	
	gtk_text_buffer_insert(buffer, &iter, sql_statment, -1);
	gtk_text_buffer_insert(buffer, &iter, "\n", -1);

	/* sql statment should end with a ';', if user forget to input it, we just add one */
	if( sql_statment[sql_statment_length - 1] != ';' ) // ';' is missing
	{
		sql_statment_checked = g_strdup_printf ("%s;", sql_statment);
		g_print("DEBUG: added ';'\n");
	} else {
		/* assign 'const char*' to 'char*' is NOT valid, such as sql_statment_checked = sql_statment */
		sql_statment_checked = g_strdup_printf ("%s", sql_statment);
	}

	/* clear the txet in entry */
	gtk_entry_set_text(GTK_ENTRY(entry), "");

	/* sqlite3_exec(database name, sql statment, callback func, user data, error msg) */
	/* if pass a struct pointer as the 4th argument of sqlite3_exec & 1st argument of callback func */
	/* gcc output a WARNING here: /
	  	warning: passing argument 3 of ‘sqlite3_exec’ from incompatible pointer type /
	 	i cannot figure it out, however, the callback function runs well /
	 To CORRECT this:
	 	decalare buffer as gobal variable, 
	 	set the 4th argument of sqlite3_exec & 1st argumen of callback func to NULL may solve it */
	rc = sqlite3_exec(builder->database, sql_statment_checked, callback, NULL, &err_msg);
	if( rc != SQLITE_OK )
	{
		gtk_text_buffer_insert(buffer, &iter, "Sql error: ", -1);
		gtk_text_buffer_insert(buffer, &iter, err_msg, -1);
		gtk_text_buffer_insert(buffer, &iter, "\n", -1);
		sqlite3_free(err_msg);
	}

	gtk_text_buffer_insert(buffer, &iter, SQL_SH, -1);

	g_free (sql_statment_checked);
}

/* Debug->Exec sql command */
void on_debug_exec_sql_command_activate(GtkMenuItem *menuitem, DatabaseBuilder *builder)
{
	gint rc;

	GtkWidget *command_window;
	GtkWidget *vbox;
	GtkWidget *hbox;

	GtkWidget *sw;
	GtkWidget *text;
	GtkWidget *label;
	GtkWidget *button;

	/* build the GUI of command window */
	command_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(command_window), 400, 300);
	gtk_window_set_transient_for(GTK_WINDOW(command_window), GTK_WINDOW(builder->window));
	gtk_window_set_position(GTK_WINDOW(command_window), GTK_WIN_POS_CENTER_ON_PARENT);
	gtk_window_set_destroy_with_parent (GTK_WINDOW (command_window), TRUE);
	gtk_window_set_title(GTK_WINDOW(command_window), "Sql Command Window");

	vbox = gtk_vbox_new(FALSE, 2);
	gtk_container_add(GTK_CONTAINER(command_window), vbox);

	sw = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(sw), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_box_pack_start(GTK_BOX(vbox), sw, TRUE, TRUE, 2);
	
	text = gtk_text_view_new();
	gtk_text_view_set_editable(GTK_TEXT_VIEW(text), FALSE);
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text), GTK_WRAP_WORD);
	gtk_container_add(GTK_CONTAINER(sw), text);

	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text));
	gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
	gtk_text_buffer_insert(buffer, &iter, "Warning! Do NOT use this command window to access database unless you know what you are doing!\n", -1);
	gtk_text_buffer_insert(buffer, &iter, "INFO: after execute a command, you must refresh main window to get data reload.\n", -1);

	hbox = gtk_hbox_new(FALSE, 2);
	gtk_box_pack_end(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	label = gtk_label_new("Command:");
	gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);

	entry = gtk_entry_new();
	gtk_entry_set_activates_default(GTK_ENTRY(entry), TRUE);
	gtk_box_pack_start(GTK_BOX(hbox), entry ,TRUE, TRUE, 0);

	button = gtk_button_new_from_stock(GTK_STOCK_OK);
	gtk_button_set_relief(GTK_BUTTON(button), GTK_RELIEF_NONE);
	gtk_box_pack_end(GTK_BOX(hbox), button, FALSE, FALSE, 0);

	/* connect the database */
	rc = sqlite3_open(builder->filename, &(builder->database));
	if(rc != SQLITE_OK) {
		gtk_text_buffer_insert(buffer, &iter, sqlite3_errmsg(builder->database), -1);
		gtk_text_buffer_insert(buffer, &iter, "\n", -1);
		sqlite3_close(builder->database);
	} else {
		gtk_text_buffer_insert(buffer, &iter, "INFO: database ", -1);
		gtk_text_buffer_insert(buffer, &iter, builder->filename, -1);
		gtk_text_buffer_insert(buffer, &iter, " open successfully\n", -1);
	}

	gtk_text_buffer_insert(buffer, &iter, SQL_SH, -1);

	g_signal_connect (G_OBJECT(command_window), "delete-event", G_CALLBACK(on_command_window_delete_event), builder->database);

	g_signal_connect (G_OBJECT(button), "clicked", G_CALLBACK(on_button_clicked), builder);
	g_signal_connect (G_OBJECT(entry), "activate", G_CALLBACK(on_button_clicked), builder);

	gtk_widget_show_all(command_window);

//	gtk_main();
}

static gboolean on_command_window_delete_event (GtkWidget *command_window, GdkEvent *event, sqlite3 *database)
{
	gtk_widget_destroy (command_window);
	sqlite3_close (database);
	
	return FALSE;
}
