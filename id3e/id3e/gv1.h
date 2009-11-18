#ifndef _GV1_H
#define _GV1_H

#include <gtk/gtk.h>
#include "id3v1.h"

typedef struct _gv1 Gv1;

Gv1 *gv1_new ();
void gv1_free (Gv1 *gv1);

Gv1 *gv1_init (Gv1 *gv1, GtkBuilder *builder);

Gv1 *gv1_reset (Gv1 *gv1);
Gv1 *gv1_set_sensitive (Gv1 *gv1, gboolean status);
gboolean gv1_is_sensitive (Gv1 *gv1);

Id3v1 *gv1_write_to_id3v1 (Gv1 *gv1, Id3v1 *tag);
Gv1 *gv1_read_from_id3v1 (Gv1 *gv1, Id3v1 *tag);

#endif /* _GV1_H */
