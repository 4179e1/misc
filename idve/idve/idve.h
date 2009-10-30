#ifndef _IDVE_H
#define _IDVE_H

#include <gtk/gtk.h>

typedef struct _idve Idve;

Idve *idve_new (void);
void idve_free (Idve *idve);

void idve_set_window (Idve * idve, GtkWidget *window);
GtkWidget *idve_get_window (Idve *idve);
void idve_window_show (Idve *idve);

void idve_set_list (Idve *idve, GtkWidget *list);
GtkWidget *idve_get_list (Idve *idve);

void idve_set_liststore (Idve *idve, GtkListStore *liststore);
GtkListStore *idve_get_liststore (Idve *idve);
void idve_liststore_insert (Idve *idve, const gchar *str);
void idve_liststore_clear (Idve *idve);

void idve_set_sidebar (Idve *idve, GtkWidget *sidebar);
GtkWidget *idve_get_sidebar (Idve *idve);
void idve_sidebar_toggle (Idve *idve);

void idve_set_statusbar (Idve *idve, GtkWidget *statusbar);
GtkWidget *idve_get_statusbar (Idve *idve);
void idve_statusbar_init (Idve *idve);
void idve_statusbar_message (Idve *idve, const char *fmt, ...);
void idve_statusbar_toggle (Idve *idve);

#endif /* _IDVE_H */
