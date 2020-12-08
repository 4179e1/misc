#include <stdio.h>
#include <locale.h>
#include <libintl.h>

#define _(STR) gettext(STR)

#define LOCALEDIR "/usr/share/locale"

#define PACKAGE "fool"

int main (void)
{
	setlocale (LC_ALL, "");

	bindtextdomain (PACKAGE, LOCALEDIR);

	textdomain (PACKAGE);

	printf (_("Hello, world!\n"));

	printf (_("中文字符串\n"));

	return 0;
}
