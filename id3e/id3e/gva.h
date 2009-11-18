#ifndef _GVA_H
#define _GVA_H

typedef struct _gva Gva;

Gva *gva_new (void);
void gva_free (Gva *gva);

Gva *gva_init (Gva *gva, GtkBuilder *builder);

#endif /* _GVA_H */
