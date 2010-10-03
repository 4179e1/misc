#include <glib-object.h>
#include "media.h"
#include "my_marshaller.h"

static void media_class_init (MediaClass *class);
static void media_set_property (GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec);
static void media_get_property (GObject *object, guint prop_id, GValue *value, GParamSpec *pspec);
static void media_unpacked (Media *media);
static gboolean media_throw_out (Media *media, gboolean permanent);


GType media_get_type (void)
{
	static GType media_type = 0;

	if (!media_type)
	{
		static const GTypeInfo media_info = 
		{
			sizeof (MediaClass), 				/* class structure size */
			NULL,								/* base class initializer */
			NULL,								/* base class finalizer */
			(GClassInitFunc)media_class_init,	/* class initializer */
			NULL,								/* class finalizer */
			NULL,								/* class data */
			sizeof (Media),						/* instance structure size */
			16,									/* preallocated instances */
			NULL,								/* instance initializer */
			NULL,								/* function table */
		};

		media_type = g_type_register_static (
				G_TYPE_OBJECT,					/* parent class */
				"Media",						/* type name */
				&media_info,					/* GTypeInfo struct (above) */
				0);								/* flags */
	}

	return media_type;
}

void media_set_orig_package (Media *object, gboolean new_value)
{
	Media *media;
	g_return_if_fail (IS_MEDIA (object));
	media = MEDIA (object);

	if (media->orig_package != new_value)
	{
		media->orig_package = new_value;
		g_object_notify (G_OBJECT (media), "orig-package");
	}
}

void media_print_inv_nr (Media *object)
{
	Media *media;

	g_return_if_fail (IS_MEDIA (object));

	media = MEDIA (object);

	g_print ("Inventory number: %d\n", media->inv_nr);
}

enum 
{
	PROP_MEDIA_0 = 0,
	PROP_INV_NR,
	PROP_ORIG_PACKAGE,
};

enum
{
	UNPACKED,
	THROW_OUT,
	LAST_SIGNAL
};

static guint media_signal[LAST_SIGNAL] = {0, 0};

static void media_class_init (MediaClass *klass)
{
	GParamSpec *inv_nr_param;
	GParamSpec *orig_package_param;
	GObjectClass *g_object_class;

	g_object_class = G_OBJECT_CLASS (klass);

	inv_nr_param = g_param_spec_uint ("inventory-id",		/* identifier */
			"inventory number", /* nickname */
			"number on inventory label", 
								/* description */
			0,					/* minimum */
			UINT_MAX,			/* maximum */
			0,					/* default */
			G_PARAM_READWRITE); /* flags */

	orig_package_param = g_param_spec_boolean ("orig-package",
			"original package?",
			"is item in its orginal package?",
			FALSE,
			G_PARAM_READWRITE);

	/* override base object methods */
	g_object_class->set_property = media_set_property;
	g_object_class->get_property = media_get_property;

	/* install properties */
	g_object_class_install_property (g_object_class, 
			PROP_INV_NR, 
			inv_nr_param);

	g_object_class_install_property (g_object_class,
			PROP_ORIG_PACKAGE,
			orig_package_param);

	/* set signal handlers */
	klass->unpacked = media_unpacked;
	klass->throw_out = media_throw_out;

	/* install signals and default handlers */
	media_signal[UNPACKED] = 
		g_signal_new ("unpacked",						/* name */
				TYPE_MEDIA,						/* class type identifier */
				G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED,	/* options */
				G_STRUCT_OFFSET (MediaClass, unpacked), /* handler offset */
				NULL,							/* accumulator function */
				NULL,							/* accumulator data */
				g_cclosure_marshal_VOID__VOID,	/* marshaller */
				G_TYPE_NONE,
				0);

	media_signal[THROW_OUT] =
		g_signal_new("throw_out",
				TYPE_MEDIA,
				G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED,
				G_STRUCT_OFFSET (MediaClass, throw_out),
				NULL, 
				NULL,
				_my_mayshal_BOOLEAN__BOOLEAN,
				G_TYPE_BOOLEAN,
				1,
				G_TYPE_BOOLEAN);
}

static void media_set_property (GObject *object,
		guint prop_id,
		const GValue *value,
		GParamSpec *pspec)
{
	Media *media;
	guint new_inv_nr;
	gboolean new_orig_package;

	media = MEDIA (object);

	switch (prop_id)
	{
		case PROP_INV_NR:
			new_inv_nr = g_value_get_uint (value);
			if (media->inv_nr != new_inv_nr)
			{
				media->inv_nr = new_inv_nr;
			}
			break;
		case PROP_ORIG_PACKAGE:
			new_orig_package = g_value_get_boolean (value);
			if (media->orig_package != new_orig_package)
			{
				media->orig_package = new_orig_package;
			}
			break;
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
			break;
	}
}

static void media_get_property (GObject *object,
		guint prop_id,
		GValue *value,
		GParamSpec *pspec)
{
	Media *media;

	media = MEDIA (object);

	switch (prop_id)
	{
		case PROP_INV_NR:
			g_value_set_uint (value, media->inv_nr);
			break;
		case PROP_ORIG_PACKAGE:
			g_value_set_boolean (value, media->orig_package);
			break;
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
			break;
	}
}

static void media_unpacked (Media *media)
{
	if (media->orig_package)
	{
		g_object_set (media, "orig-package", FALSE, NULL);
		g_print ("DEFALUT HANDLER: Media unpacked.\n");
	}
	else
	{
		g_print ("DEFALUT HANDLER: Media already unpacked.\n");
	}
}

static gboolean media_throw_out (Media *media, gboolean permanent)
{
	if (permanent)
	{
		g_print ("DEFALUT HANDLER: Trash media.\n");
	}
	else
	{
		g_print ("DEFALUT HANDLER: Media not in dumpster quite yet.\n");
	}

	return permanent;
}
