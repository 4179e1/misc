#ifndef _ENC_H
#define _ENC_H

#include <gtk/gtk.h>

#ifndef _ID3E_ENC
#define _ID3E_ENC
typedef struct _enc Enc;
#endif /* _ID3E_ENC */

Enc *enc_new (void);
void enc_free (Enc *enc);

Enc *enc_init (Enc *enc, GtkBuilder *builder);
Enc *enc_reset (Enc *enc);

GtkEntry *enc_get_src_entry (Enc *enc);
GtkEntry *enc_get_dest_entry (Enc *enc);
GtkListStore *enc_get_list_store (Enc *enc);

gchar *enc_get_src_text (Enc *enc);
gchar *enc_get_dest_text (Enc *enc);
gchar *enc_set_src_text (Enc *enc, gchar *text);
gchar *enc_set_dest_text (Enc *enc, gchar *text);

gchar *enc_get_src_active_text (Enc *enc);
gchar *enc_get_dest_active_text (Enc *enc);

/* FIXME: we may not need this 4 func */
gint enc_get_src_active (Enc *enc);
gint enc_get_dest_active (Enc *enc);
gint enc_set_src_active (Enc *enc, gint index);
gint enc_set_dest_active (Enc *enc, gint index);

gboolean enc_get_src_active_iter (Enc *enc, GtkTreeIter *iter);
gboolean enc_get_dest_active_iter (Enc *enc, GtkTreeIter *iter);
void enc_set_src_active_iter (Enc *enc, GtkTreeIter *iter);
void enc_set_dest_active_iter (Enc *enc, GtkTreeIter *iter);

#endif /* _ENC_H */
