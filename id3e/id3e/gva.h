#ifndef _GVA_H
#define _GVA_H

#include <gtk/gtk.h>
#include "id3.h"

#ifndef _ID3E_GVA
#define _ID3E_GVA
typedef struct _gva Gva;
#endif /* _ID3E_GVA */

Gva *gva_new ();
void gva_free (Gva *gva);

Gva *gva_init (Gva *gva, GtkBuilder *builder);

Gva *gva_reset (Gva *gva);
Gva *gva_set_sensitive (Gva *gva, gboolean status);
gboolean gva_is_sensitive (Gva *gva);

Id3 *gva_write_to_id3 (Gva *gva, Id3 *id3);
Gva *gva_read_from_id3 (Gva *gva, Id3 *id3);

#endif /* _GVA_H */
