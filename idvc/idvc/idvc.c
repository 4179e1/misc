#include <gtk/gtk.h>
#include "idvc.h"

struct _idvc
{
	GtkWidget *window;
	GtkWidget *list;
	GtkWidget *statusbar;
};

Idvc *idvc_new (void)
{
	Idvc *idvc;

	idvc = g_slice_new (Idvc);
	idvc->window = NULL;
	idvc->list = NULL;
	idvc->statusbar = NULL;

	return idvc;
}

void idvc_free (Idvc *idvc_info)
{
	g_slice_free (Idvc, idvc_info);
}

void idvc_set_window (Idvc *idvc_info, GtkWidget *window)
{
	idvc_info->window = window;
}

GtkWidget *idvc_get_window (Idvc *idvc_info)
{
	return idvc_info->window;
}

void idvc_set_list (Idvc *idvc_info, GtkWidget *list)
{
	idvc_info->list = list;
}

GtkWidget *idvc_get_list (Idvc *idvc_info)
{
	return idvc_info->list;
}

void idvc_set_statusbar (Idvc *idvc_info, GtkWidget *statusbar)
{
	idvc_info->statusbar = statusbar;
}

GtkWidget *idvc_get_statusbar (Idvc *idvc_info)
{
	return idvc_info->statusbar;
}
