#include <stdio.h>
#include "wpstdio.h"
#include "wpbase.h"

int wp_remove (const char *path)
{
	int n;
	if ((n = remove (path)) == -1)
		wp_error_sys_warning ("remove error");
	return n;
}

int wp_rename (const char *oldname, const char *newname)
{
	int n;
	if ((n = rename (oldname, newname)) == -1)
		wp_error_sys_warning ("rename error");
	return n;
}
