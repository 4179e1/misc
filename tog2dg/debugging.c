#include <stdio.h>
#include <glib.h>

void func(char* str) {
	g_print ("%s\n", str);
}

gboolean func2(int i) {
	g_return_val_if_fail ((i >= 2), FALSE);
	g_assert_not_reached();
	if (i >= 2) {
		return TRUE;
	} else {
		return FALSE;
	}

	/* should not be reached */
	g_return_val_if_reached (FALSE);
	g_assert_not_reached();

	return TRUE;
}


int main(int argc, char* argv[]) {
	g_assert (argc >= 2);

	if (func2(argc)) {
		g_print ("args ok\n");
	} else {
		g_print ("args error\n");
	}
	

	func(argv[1]);

	return 0;
}
