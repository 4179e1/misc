#include "wpstdsys.h"
#include "wpbase.h"

time_t wp_time (time_t *calptr)
{
	time_t t;
	if ((t = time (calptr)) == -1)
		wp_error_warning ("time error");
	return t;
}

time_t wp_mktime (struct tm *tmptr)
{
	time_t t;
	if ((t = mktime (tmptr)) == -1)
		wp_error_warning ("mktime error");
	return t;
}
