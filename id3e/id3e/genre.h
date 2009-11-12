#ifndef _GENRE_H
#define _GENRE_H

#include <gtk/gtk.h>

void genre_list_init (GtkListStore *liststore);
const gchar *get_genre (int id);

#endif /* _GENRE */
