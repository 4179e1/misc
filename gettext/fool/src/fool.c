#include <stdio.h>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "gettext.h"

#define _(STR) gettext(STR)
#define N_(STR) STR

char *gs = N_("Global string\n");

int main (void)
{
	setlocale (LC_ALL, "");

	bindtextdomain (PACKAGE, LOCALEDIR);

	textdomain (PACKAGE);

	printf (_("Hello, world!\n"));
	printf (_(gs));

	return 0;
}
