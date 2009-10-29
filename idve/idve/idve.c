#include <gtk/gtk.h>
#include "idve.h"

/* struct for idve, passed as the argument to all callback func  */
struct _idve
{
	GtkWidget *window;
	GtkWidget *list;
	GtkWidget *statusbar;
	gint statusbar_context_id;
};


/* memory alloc */
Idve *idve_new (void)
{
	Idve *idve;

	idve = g_slice_new (Idve);
	idve->window = NULL;
	idve->list = NULL;
	idve->statusbar = NULL;

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


GObject *Gtk_builder_get_object (GtkBuilder *builder, const gchar *name)
{
	GObject *obj;

	if ((obj = gtk_builder_get_object (builder, name)) == NULL)
	{
		g_warning ("gtk_builder_get_object: %s failed!", name);
	}

	return obj;
}
