#ifndef _GENRE_H
#define _GENRE_H

#include <glib.h>

void genre_list_init (GtkListStore *liststore);
const gchar *get_genre (gchar id);
gboolean genre_valid (gchar id);

#endif /* _GENRE */
