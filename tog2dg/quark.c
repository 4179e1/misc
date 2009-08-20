#include <stdio.h>
#include <glib.h>

int main(void) {
	GQuark quark;
	GQuark quarkb;

	quark = g_quark_from_string ("orz");
	printf ("quark value %d string: %s\n", quark, g_quark_to_string (quark));

	if ((quarkb = g_quark_try_string("orz"))) {
		printf ("string %s already exist\n", g_quark_to_string(quarkb));
	}

	return 0;
}
