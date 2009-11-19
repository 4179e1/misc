#ifndef _ENC_H
#define _ENC_H

typedef struct _enc Enc;

Enc *enc_new (void);
void enc_free (Enc *enc);

Enc *enc_init (Enc *enc, GtkBuilder *builder);
Enc *enc_reset (Enc *enc);

gchar *enc_get_src (Enc *enc);
gchar *enc_get_dest (Enc *enc);
gchar *enc_set_src (Enc *enc, gchar *codeset);
gchar *enc_set_dest (Enc *enc, gchar *codeset);
#endif /* _ENC_H */
