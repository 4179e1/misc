#include <locale.h>
#include <config.h>
#include <stdio.h>
#include "module.h"
#include "gettext.h"
#define _(STR) gettext(STR)
void module_print (void)
{
	printf (_("test module\n"));
	printf (_("another test\n"));
}

void module_print2 (void)
{
	printf (_("another module\n"));
	printf (_("中文字符串\n"));
}
