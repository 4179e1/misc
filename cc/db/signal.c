#include <gtk/gtk.h>
#include <stdlib.h>
#include <assert.h>
#include "comman.h"
#include "signal.h"
#include "file_menu.h"
#include "edit_menu.h"

void show_message(DataBaseBuilder *dbb, char *message)
{
	GtkWidget *dialog;
	dialog = gtk_message_dialog_new(GTK_WINDOW(dbb->window),
			GTK_DIALOG_DESTROY_WITH_PARENT,
			GTK_MESSAGE_INFO,
			GTK_BUTTONS_OK,
			message);
	gtk_window_set_title(GTK_WINDOW(dialog), "Message");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}

int check_for_save(DataBaseBuilder *dbb)
{
	GtkWidget *dialog;
	gint result;
			
	dialog = gtk_message_dialog_new(GTK_WINDOW(dbb->window),
					GTK_DIALOG_DESTROY_WITH_PARENT,
					GTK_MESSAGE_QUESTION,
					GTK_BUTTONS_YES_NO,
					"Save database file?");
	gtk_dialog_add_button(GTK_DIALOG(dialog), GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL);
	gtk_window_set_title(GTK_WINDOW(dialog), "Question");

	result = gtk_dialog_run(GTK_DIALOG(dialog));

	gtk_widget_destroy(dialog);

	return result;
}


/* While closing the window , return FALSE to destroy window*/
gboolean on_window_delete_event(GtkWidget *window, GdkEvent *event, DataBaseBuilder *dbb)
{
	if(dbb->new_db)
	{
		if(dbb->need_saved) 
		{
			int result = check_for_save(dbb);

			switch(result)
			{
				case GTK_RESPONSE_YES:	
					g_print("TODO: save database\n");
					if(on_file_save_activate(NULL, dbb))	// if file saved, quit, else, don't quit
					{
						gtk_main_quit();
						return FALSE;
					}
					break;
				case GTK_RESPONSE_NO:
					gtk_main_quit();
					remove(dbb->database_name);
					g_print("INFO: %s deleted\n, quit", dbb->database_name);
					free(dbb->database_name);
					return FALSE;
					break;
				case GTK_RESPONSE_CANCEL:
					g_print("INFO: cancel selected, do nothing\n");
					break;
				default:
					break;
			}



			return TRUE;
		} else {
			remove(dbb->database_name);
			g_print("INFO: %s deleted, quit\n", dbb->database_name);
			free(dbb->database_name);
			gtk_main_quit();
			return FALSE;
		}
	}
	else
	{
		g_print("INFO: nothing need to be done, quit\n");
		gtk_main_quit();
		return FALSE;
	}

	/* ruturn is  not necessary here, because the programme would NEVER go through it,/
	   but add this to avoid compiler warning */
	assert(FALSE);
	return TRUE;
}


/* 3 buttons on toolbar */
void on_tool_button_add_clicked(GtkButton *button, DataBaseBuilder *dbb)
{
	on_edit_add_activate(NULL, dbb);
}

void on_tool_button_edit_clicked(GtkButton *button, DataBaseBuilder *dbb)
{
	on_edit_edit_activate(NULL, dbb);
}

void on_tool_button_delete_clicked(GtkButton *button, DataBaseBuilder *dbb)
{
	on_edit_delete_activate(NULL, dbb);
}

