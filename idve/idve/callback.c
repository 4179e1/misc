#include <gtk/gtk.h>
#include "idve.h"
#include "callback.h"

G_MODULE_EXPORT 
void on_liststore_insert (gpointer *widget, Idve *idve)
{
	idve_liststore_insert (idve, "testing msg");
}

G_MODULE_EXPORT 
void on_liststore_clear (gpointer *widget, Idve *idve)
{
	idve_liststore_clear (idve);
}


G_MODULE_EXPORT 
void on_sidebar_toggle (gpointer *widget, Idve *idve)
{
	idve_sidebar_toggle (idve);
}

G_MODULE_EXPORT 
void on_statusbar_toggle (gpointer *widget, Idve *idve)
{
	idve_statusbar_toggle (idve);
}
