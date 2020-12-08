#include <gtk/gtk.h>
#include "reg.h"
#include "handler.h"

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

void message (const gchar *message)
{
	GtkWidget *dialog;

	/* log to terminal window */
	g_warning (message);

	/* create an error message dialog and display modally to user */
	dialog = gtk_message_dialog_new (NULL,
									 GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
									 GTK_MESSAGE_INFO,
									 GTK_BUTTONS_OK,
									 message);

	gtk_window_set_title (GTK_WINDOW (dialog), "OK!");
	gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (dialog);
}
