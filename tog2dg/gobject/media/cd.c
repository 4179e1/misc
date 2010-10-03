#include "cd.h"

static void cd_class_init (CDClass *klass);
static void cd_get_property (GObject *object, guint prop_id, GValue *value, GParamSpec *pspec);
static void cd_set_property (GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec);
static void unpacked_cd ();

static void cd_cleanable_init (gpointer interface, gpointer data);

GType cd_get_type (void)
{
	static GType cd_type = 0;

	if (!cd_type)
	{
		static const GTypeInfo cd_info = 
		{
			sizeof (CDClass),
			NULL,
			NULL,
			(GClassInitFunc)cd_class_init,
			NULL,
			NULL,
			sizeof(CD),
			16,
			NULL,
			NULL,
		};
		cd_type = g_type_register_static (TYPE_MEDIA, "CompactDisc", &cd_info, 0);

#if 1
		const GInterfaceInfo cleanable_info = 
		{
			cd_cleanable_init,
			NULL,
			NULL,
		};

		g_type_add_interface_static (cd_type, TYPE_CLEANABLE, &cleanable_info);
#endif
	}

	return cd_type;
}

void clean (Cleanable *cleanable)
{
	//g_assert (IS_CD (CD (cleanable)));

	CleanableClass *interface;

	g_return_if_fail (IS_CLEANABLE(cleanable));

	interface = CLEANABLE_GET_CLASS(cleanable);

	g_object_ref (cleanable);

	interface->clean (cleanable);

	g_object_unref (cleanable);
}

enum
{
	PROP_0_CD = 0,
	PROP_WRITABLE,
};

static void unpacked_cd ()
{
	g_print ("Hi!\n");
}

static void cd_class_init (CDClass *klass)
{
	GObjectClass *g_object_class;
	MediaClass *media_class;

	media_class = MEDIA_CLASS (klass);
	media_class->unpacked = unpacked_cd;

	g_object_class = G_OBJECT_CLASS (klass);
	g_object_class->set_property = cd_set_property;
	g_object_class->get_property = cd_get_property;

	g_object_class_install_property (
			g_object_class,
			PROP_WRITABLE,
			g_param_spec_boolean ("writable", "Writable?",
				"Is the CD writeable?", FALSE,
				G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY));
}

static void cd_set_property (GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec)
{
	gboolean writable;

	CD *cd = CD(object);

	switch (prop_id)
	{
		case PROP_WRITABLE:
			writable = g_value_get_boolean (value);
			if (cd->writable != writable)
			{
				cd->writable = writable;
			}
			break;

		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
			break;
	}
}

static void cd_get_property (GObject *object, guint prop_id, GValue *value, GParamSpec *pspec)
{
	CD *cd = CD (object);

	switch (prop_id)
	{
		case PROP_WRITABLE:
			g_value_set_boolean (value, cd->writable);
			break;
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
			break;
	}
}

static void cd_clean (Cleanable *cleanable)
{
	g_assert (IS_CD(CD(cleanable)));

	g_print ("cleaning CD.\n");
}

static void cd_cleanable_init (gpointer interface, gpointer data)
{
	CleanableClass *cleanable = interface;

	g_assert (G_TYPE_FROM_INTERFACE(cleanable) == TYPE_CLEANABLE);
	/* is the interface ready? */
	//g_assert (cleanable_base_init_count > 0);

	cleanable->clean = cd_clean;
}
