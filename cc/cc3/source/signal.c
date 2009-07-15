#include <gtk/gtk.h>

gboolean on_window_delete_event(GtkWidget *window, GdkEvent *event, gpointer user_data)
{
	GtkWidget *dialog;
	gint result;

	dialog = gtk_message_dialog_new(GTK_WINDOW(window),
			GTK_DIALOG_DESTROY_WITH_PARENT,
			GTK_MESSAGE_QUESTION,
			GTK_BUTTONS_YES_NO,
			"Save changes to database?");
	gtk_dialog_add_button(GTK_DIALOG(dialog), GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL);
	gtk_window_set_title(GTK_WINDOW(dialog), "Question");
	result = gtk_dialog_run(GTK_DIALOG(dialog));

	switch(result)
	{
		case GTK_RESPONSE_YES:
			g_print("TODO\n");
			gtk_main_quit();
			break;
		case GTK_RESPONSE_NO:
			gtk_main_quit();
			break;
		case GTK_RESPONSE_CANCEL:
			break;
		default:
			break;
	}

	gtk_widget_destroy(dialog);

	return TRUE;
}
