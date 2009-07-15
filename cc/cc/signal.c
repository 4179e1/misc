#include <gtk/gtk.h>
#include "comman.h"
#include "signal.h"

gboolean on_window_delete_event(GtkWidget *window, GdkEvent *event, DataBaseBuilder *dbb)
{
	if(dbb->need_saved) 
	{
		GtkWidget *dialog;
		gint result;
	
		dialog = gtk_message_dialog_new(GTK_WINDOW(window),
				GTK_DIALOG_DESTROY_WITH_PARENT,
				GTK_MESSAGE_QUESTION,
				GTK_BUTTONS_YES_NO,
				"Save database file?");
		gtk_dialog_add_button(GTK_DIALOG(dialog), GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL);
		gtk_window_set_title(GTK_WINDOW(dialog), "Question");
		result = gtk_dialog_run(GTK_DIALOG(dialog));

		switch(result)
		{
			case GTK_RESPONSE_YES:
				g_print("TODO: save database\n");
				gtk_main_quit();
				break;
			case GTK_RESPONSE_NO:
				gtk_main_quit();
				remove(dbb->database_name_temp);
				break;
			case GTK_RESPONSE_CANCEL:
				break;
			default:
				break;
		}

		gtk_widget_destroy(dialog);

		return TRUE;
	} else {
		remove(dbb->database_name_temp);
		gtk_main_quit();
	}

	/* ruturn is  not necessary here, because the programme would NEVER go through it,/
	   but add this to avoid compiler warning */
	return TRUE;
}
