
#ifndef ___my_mayshal_MARSHAL_H__
#define ___my_mayshal_MARSHAL_H__

#include	<glib-object.h>

G_BEGIN_DECLS

/* INT:VOID (my_marshaller.list:1) */
extern void _my_mayshal_INT__VOID (GClosure     *closure,
                                   GValue       *return_value,
                                   guint         n_param_values,
                                   const GValue *param_values,
                                   gpointer      invocation_hint,
                                   gpointer      marshal_data);

/* VOID:OBJECT,INT (my_marshaller.list:2) */
extern void _my_mayshal_VOID__OBJECT_INT (GClosure     *closure,
                                          GValue       *return_value,
                                          guint         n_param_values,
                                          const GValue *param_values,
                                          gpointer      invocation_hint,
                                          gpointer      marshal_data);

/* UINT:BOOLEAN (my_marshaller.list:3) */
extern void _my_mayshal_UINT__BOOLEAN (GClosure     *closure,
                                       GValue       *return_value,
                                       guint         n_param_values,
                                       const GValue *param_values,
                                       gpointer      invocation_hint,
                                       gpointer      marshal_data);

/* BOOLEAN:BOOLEAN (my_marshaller.list:4) */
extern void _my_mayshal_BOOLEAN__BOOLEAN (GClosure     *closure,
                                          GValue       *return_value,
                                          guint         n_param_values,
                                          const GValue *param_values,
                                          gpointer      invocation_hint,
                                          gpointer      marshal_data);

G_END_DECLS

#endif /* ___my_mayshal_MARSHAL_H__ */

