#include <stdio.h>
#include <glib.h>

int main (void) {
	gint* p;
	//p = (gint*) g_malloc (sizeof(int)*10);
	p = g_new(gint, 10);
	int i;
	for (i = 0; i < 10; i++) {
		p[i] = i;
		printf ("%d\t", p[i]);
	}
	printf ("\n");
	return 0;
}
