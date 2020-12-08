#ifndef __CLEANABLE_H_
#define __CLEANABLE_H_

#include <glib.h>
#include <glib-object.h>

typedef struct _cleanable Cleanable;

typedef struct _cleanable_class
{
	GTypeInterface base_interface;
	void (*clean)(Cleanable *object);
} CleanableClass;

GType cleanable_get_type();

#define TYPE_CLEANABLE (cleanable_get_type())

#define CLEANABLE(object) \
	(G_TYPE_CHECK_INSTANCE_CAST((object), TYPE_CLEANABLE, Cleanable))

#define IS_CLEANABLE(object) \
	(G_TYPE_CHECK_INSTANCE_TYPE((object), TYPE_CLEANABLE))

#define CLEANABLE_GET_CLASS(object) \
	(G_TYPE_INSTANCE_GET_INTERFACE((object), TYPE_CLEANABLE, CleanableClass))

#endif /* __CLEANABLE_H_ */
