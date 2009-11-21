#ifndef _ID3E_H
#define _ID3E_H

#include <gtk/gtk.h>
#include "enc.h"
#include "gva.h"

#if 0
/* the modules are not designed very well... */
#ifndef _ID3E_ENC
#define _ID3E_ENC
typedef struct _enc Enc;
#endif /* _ID3E_ENC */

#ifndef _ID3E_GVA
#define _ID3E_GVA
typedef struct _gva Gva;
#endif /* _ID3E_GVA */
#endif

typedef struct _id3e Id3e;

Id3e *id3e_new (void);
void id3e_free (Id3e *id3e);

Id3e *id3e_init (Id3e *id3e, GtkBuilder *builder);

void id3e_set_window (Id3e * id3e, GtkWidget *window);
GtkWidget *id3e_get_window (Id3e *id3e);
void id3e_window_show (Id3e *id3e);

void id3e_set_list (Id3e *id3e, GtkWidget *list);
GtkWidget *id3e_get_list (Id3e *id3e);
void id3e_list_init (Id3e *id3e);
GtkListStore *id3e_get_list_store (Id3e *id3e);
void id3e_list_insert (Id3e *id3e, const gchar *path);
gint id3e_list_get_selected_count (Id3e *id3e);
GList *id3e_list_get_selectd_rows (Id3e *id3e);

void id3e_set_sidebar (Id3e *id3e, GtkWidget *sidebar);
GtkWidget *id3e_get_sidebar (Id3e *id3e);
void id3e_sidebar_toggle (Id3e *id3e);

void id3e_set_statusbar (Id3e *id3e, GtkWidget *statusbar);
GtkWidget *id3e_get_statusbar (Id3e *id3e);
void id3e_statusbar_init (Id3e *id3e);
void id3e_statusbar_message (Id3e *id3e, const char *fmt, ...);
void id3e_statusbar_toggle (Id3e *id3e);

void id3e_set_enc (Id3e *id3e, Enc *enc);
Enc *id3e_get_enc (Id3e *id3e);

void id3e_set_gva (Id3e *id3e, Gva *gva);
Gva *id3e_get_gva (Id3e *id3e);

gpointer id3e_pointer_aquire (Id3e *id3e, gpointer data);
gpointer id3e_pointer_release (Id3e *id3e);
gpointer id3e_get_pointer (Id3e *id3e);
gboolean id3e_pointer_is_available (Id3e *id3e);

#endif /* _IDVE_H */
