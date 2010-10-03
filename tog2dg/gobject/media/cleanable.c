#include "cleanable.h"

static guint cleanable_base_init_count = 0;

static void cleanable_base_init (CleanableClass *cleanable)
{
	cleanable_base_init_count++;

	if (cleanable_base_init_count == 1)
	{
		/* "constructor" code, for example, register signals */
	}
}

static void cleanable_base_finalize (CleanableClass *cleanable)
{
	cleanable_base_init_count--;

	if (cleanable_base_init_count == 0)
	{
		/* "destructor" code, for example, unregister signals */
	}
}

GType cleanable_get_type (void)
{
	static GType cleanable_type = 0;

	if (!cleanable_type)
	{
		static const const GTypeInfo cleanable_info = 
		{
			sizeof (CleanableClass),
			(GBaseInitFunc) cleanable_base_init,
			(GBaseFinalizeFunc) cleanable_base_finalize,
		};

		cleanable_type = g_type_register_static (G_TYPE_INTERFACE, "Cleanable", &cleanable_info, 0);
	}

	return cleanable_type;
}



