#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "comman.h"
#include "debug_menu.h"

#define SQL_SH "sqlite> "


/* Debug->Clear database */
void on_debug_clear_database_activate(GtkMenuItem *menuitem, DataBaseBuilder *dbb)
{

}


/* Debug->Exec sql command */
static GtkTextIter iter;
static gboolean col_name_printed;

GtkTextBuffer *buffer;
GtkWidget *entry;

/* according the numbers of rows that sqlite return,
   callback func will run exactly the number of times */
static int callback(void *unused, int argc, char **argv, char **col_name){
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

void on_button_clicked(GtkButton *button, DataBaseBuilder *dbb)
{
	int rc;
	char *err_msg;
	const char *sql_statment;
	char sql_statment_checked[MAX_SQL_STATMENT_LENGTH];
	int sql_statment_length;

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

	/* sql statment should end with a ';', if user forget to input it, we just add one /
	   to do this, we need another string to save the modified sql statment, /
	   so we need to check the length of the statmen to ensure it can be store in the string we defined */
	if( sql_statment_length > MAX_SQL_STATMENT_LENGTH - 2 )	//statment too long
	{
		gtk_text_buffer_insert(buffer, &iter, "Error: Sql statment too long\n", -1); 
		return; // return to avoid error;
	}

	if( sql_statment[sql_statment_length - 1] != ';' ) // ';' is missing
	{
		sprintf(sql_statment_checked, "%s;", sql_statment);
		g_print("DEBUG: added ';'\n");
	} else {
		/* assign 'const char*' to 'char*' is NOT valid, such as sql_statment_checked = sql_statment */
		strcpy(sql_statment_checked, sql_statment);
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
	rc = sqlite3_exec(dbb->db, sql_statment_checked, callback, NULL, &err_msg);
	if( rc != SQLITE_OK )
	{
		gtk_text_buffer_insert(buffer, &iter, "Sql error: ", -1);
		gtk_text_buffer_insert(buffer, &iter, err_msg, -1);
		gtk_text_buffer_insert(buffer, &iter, "\n", -1);
		sqlite3_free(err_msg);
	} else {
		if(dbb->new_db)
			dbb->need_saved = TRUE;
	}

	gtk_text_buffer_insert(buffer, &iter, SQL_SH, -1);
}

/* Debug->Exec sql command */
void on_debug_exec_sql_command_activate(GtkMenuItem *menuitem, DataBaseBuilder *dbb)
{
	int rc;

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
	gtk_window_set_transient_for(GTK_WINDOW(command_window), GTK_WINDOW(dbb->window));
	gtk_window_set_position(GTK_WINDOW(command_window), GTK_WIN_POS_CENTER_ON_PARENT);
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
	rc = sqlite3_open(dbb->database_name, &(dbb->db));
	if(rc != SQLITE_OK) {
		gtk_text_buffer_insert(buffer, &iter, sqlite3_errmsg(dbb->db), -1);
		gtk_text_buffer_insert(buffer, &iter, "\n", -1);
		sqlite3_close(dbb->db);
	} else {
		gtk_text_buffer_insert(buffer, &iter, "INFO: datbase ", -1);
		gtk_text_buffer_insert(buffer, &iter, dbb->database_name, -1);
		gtk_text_buffer_insert(buffer, &iter, "open successfully\n", -1);
	}

	gtk_text_buffer_insert(buffer, &iter, SQL_SH, -1);

	g_signal_connect_swapped(G_OBJECT(command_window), "destroy", G_CALLBACK(gtk_main_quit), G_OBJECT(command_window));

	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(on_button_clicked), dbb);
	g_signal_connect(G_OBJECT(entry), "activate", G_CALLBACK(on_button_clicked), dbb);

	gtk_widget_show_all(command_window);

//	gtk_main();
	
//	sqlite3_close(dbb->db);
}
