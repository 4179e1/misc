#ifndef _IDVC_H
#define _IDVC_H

typedef struct _idvc Idvc;

Idvc *idvc_new (void);
void idvc_free (Idvc *divc_info);

void idvc_set_window (Idvc *idvc_info, GtkWidget *window);
GtkWidget *idvc_get_window (Idvc *idvc_info);

void idvc_set_list (Idvc *idvc_info, GtkWidget *list);
GtkWidget *idvc_get_list (Idvc *idvc_info);

void idvc_set_statusbar (Idvc *idvc_info, GtkWidget *statusbar);
GtkWidget *idvc_get_statusbar (Idvc *idvf_info);
#endif /* _IDVC_H */
