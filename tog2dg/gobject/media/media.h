#ifndef _MEDIA_H
#define _MEDIA_H
#include <glib.h>
#include <glib-object.h>

G_BEGIN_DECLS

typedef struct _media
{
	GObject parent_instance;

	guint inv_nr;
	GString *title;
	GString *location;
	gboolean orig_package;
} Media;

typedef struct _media_class
{
	GObjectClass parent_class;

	void (*unpacked)(Media *media);
	gboolean (*throw_out)(Media *media, gboolean permanent);
} MediaClass;

#define TYPE_MEDIA (media_get_type())

#define MEDIA(object) \
	(G_TYPE_CHECK_INSTANCE_CAST ((object), TYPE_MEDIA, Media))

#define MEDIA_CLASS(klass) \
	(G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_MEDIA, MediaClass))

#define IS_MEDIA(object) \
	(G_TYPE_CHECK_INSTANCE_TYPE ((object), TYPE_MEDIA))

#define IS_MEDIA_CLASS(klass) \
	(G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_MEDIA))

#define MEDIA_GET_CLASS(object) \
	(G_TYPE_INSTANCE_GET_CLASS ((object), TYPE_MEDIA))

GType media_get_type (void);

void media_print_inv_nr (Media *media);

void media_set_orig_package (Media *object, gboolean new_value);

G_END_DECLS

#endif /* _MEDIA_H */
