#if 0
gcc -o `basename $0 .c` -Wall -O2 $0 `pkg-config --libs --cflags glib-2.0 gobject-2.0`
exit
#endif

#include <glib-object.h>
#include <stdio.h>

int main (int argc, char **argv)
{
	GValue *value;

	/* initialize type system */
	g_type_init();

	/* allocate */
	value = g_new0 (GValue, 1);

	/* initialize GValue type to gint */
	g_value_init (value, G_TYPE_INT);

	g_value_set_int (value, 42);
	g_print ("Value: %d\n", g_value_get_int (value));

	if (G_VALUE_HOLDS_OBJECT (value))
	{
		g_print ("Container holds a GObject\n");
	}
	else
	{
		g_print ("Container does not hold a GObject\n");
	}

	g_free (value);

	return 0;
}
