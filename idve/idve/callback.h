#ifndef _CALLBACK_H
#define _CALLBACK_H

#include <gtk/gtk.h>
#include "idve.h"

void on_liststore_insert (gpointer *widget, Idve *idve);
void on_liststore_clear (gpointer *widget, Idve *idve);

void on_sidebar_toggle (gpointer *widget, Idve *idve);

void on_statusbar_toggle (gpointer *widget, Idve *idve);
#endif /* _CALLBACK_H */
