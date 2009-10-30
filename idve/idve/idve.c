#include <gtk/gtk.h>
#include "idve.h"

/* struct for idve, passed as the argument to all callback func  */
struct _idve
{
	GtkWidget *window;

	GtkWidget *list;
	GtkListStore *liststore;

	GtkWidget *sidebar;
	gboolean sidebar_is_shown;

	GtkWidget *statusbar;
	gboolean statusbar_is_shown;
	gint statusbar_context_id;
};


/* memory alloc */
Idve *idve_new (void)
{
	Idve *idve;

	idve = g_slice_new (Idve);
	idve->window = NULL;

	idve->list = NULL;
	idve->liststore = NULL;

	idve->sidebar = NULL;
	idve->sidebar_is_shown = TRUE;

	idve->statusbar = NULL;
	idve->statusbar_is_shown = TRUE;

	return idve;
}

void idve_free (Idve *idve)
{
	g_slice_free (Idve, idve);
}

/* window */
void idve_set_window (Idve *idve, GtkWidget *window)
{
	idve->window = window;
}

GtkWidget *idve_get_window (Idve *idve)
{
	return idve->window;
}

void idve_window_show (Idve *idve)
{
	gtk_widget_show (GTK_WIDGET (idve->window));
}

/* listview */
void idve_set_list (Idve *idve, GtkWidget *list)
{
	idve->list = list;
}

GtkWidget *idve_get_list (Idve *idve)
{
	return idve->list;
}

/* liststore */
void idve_set_liststore (Idve *idve, GtkListStore *liststore)
{
	idve->liststore = liststore;
}

GtkListStore *idve_get_liststore (Idve *idve)
{
	return idve->liststore;
}

void idve_liststore_insert (Idve *idve, const gchar *str)
{
	GtkTreeIter iter;

	gtk_list_store_append (idve->liststore, &iter);
	gtk_list_store_set (idve->liststore, &iter,
			0, str,
			-1);
}

void idve_liststore_clear (Idve *idve)
{
	gtk_list_store_clear (idve->liststore);
}

/* sidebar */
void idve_set_sidebar (Idve *idve, GtkWidget *sidebar)
{
	idve->sidebar = sidebar;
}

GtkWidget *idve_get_sidebar (Idve *idve)
{
	return idve->sidebar;
}

void idve_sidebar_toggle (Idve *idve)
{
	if (idve->sidebar_is_shown)
	{
		gtk_widget_hide (idve->sidebar);
		idve->sidebar_is_shown = FALSE;
	}
	else
	{
		gtk_widget_show (idve->sidebar);
		idve->sidebar_is_shown = TRUE;
	}
}

/* statusbar */
void idve_set_statusbar (Idve *idve, GtkWidget *statusbar)
{
	idve->statusbar = statusbar;
}

GtkWidget *idve_get_statusbar (Idve *idve)
{
	return idve->statusbar;
}

void idve_statusbar_init (Idve *idve)
{
	idve->statusbar_context_id = gtk_statusbar_get_context_id (GTK_STATUSBAR (idve->statusbar), "IDV Editor Ready!");
}

void idve_statusbar_message (Idve *idve, const char *fmt, ...)
{
	gchar *msg;
	va_list ap;

	va_start (ap, fmt);
	msg = g_strdup_vprintf (fmt, ap);
	va_end (ap);

	gtk_statusbar_pop (GTK_STATUSBAR (idve->statusbar), 
			idve->statusbar_context_id);
	gtk_statusbar_push (GTK_STATUSBAR (idve->statusbar),
			idve->statusbar_context_id, msg);

	g_free (msg);
}

void idve_statusbar_toggle (Idve *idve)
{
	if (idve->statusbar_is_shown)
	{
		gtk_widget_hide (idve->statusbar);
		idve->statusbar_is_shown = FALSE;
	}
	else
	{
		gtk_widget_show (idve->statusbar);
		idve->statusbar_is_shown = TRUE;
	}
}
