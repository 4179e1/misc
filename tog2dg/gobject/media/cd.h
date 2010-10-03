#ifndef __CD_H_
#define __CD_H_

#include <glib.h>
#include <glib-object.h>
#include "media.h"
#include "cleanable.h"

G_BEGIN_DECLS

typedef struct _cd
{
	Media media_instance;
	gboolean writable;
} CD;

typedef struct _cd_class
{
	MediaClass media_class;
} CDClass;

#define TYPE_CD (cd_get_type())
#define CD(object) \
	(G_TYPE_CHECK_INSTANCE_CAST((object), TYPE_CD, CD))
#define CD_CLASS(klass) \
	(G_TYPE_CHECK_CLASS_CAST((object), TYPE_CD, CDClass))
#define IS_CD(object) \
	(G_TYPE_CHECK_INSTANCE_TYPE((object), TYPE_CD))
#define IS_CD_CLASS(klass) \
	(G_TYPE_CHECK_CLASS_TYPE((klass), TYPE_CD))
#define CD_GET_CLASS(object) \
	(G_TYPE_INSTANCE_GET_CLASS((object), TYPE_CD, CDClass))

GType cd_get_type (void);
void clean (Cleanable *cleanable);

G_END_DECLS

#endif /* __CD_H_ */
