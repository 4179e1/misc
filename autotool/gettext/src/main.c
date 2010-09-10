#include <config.h>
#include <locale.h>
#include "gettext.h"
#include <stdio.h>
#include "module.h"
#define _(STR) gettext(STR)

void func (void)
{
	printf (_("this is a func\n"));
}

int main (void)
{
	setlocale (LC_ALL, "");
	textdomain (PACKAGE);
	bindtextdomain (PACKAGE, LOCALEDIR);

	printf ("%s: %s\n", PACKAGE, LOCALEDIR);

	func();

	printf (_("test program start\n"));
	module_print ();
	module_print2 ();

	printf (_("test program end\n"));

	return 0;
}
