#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "wpbase.h"

#ifdef OPEN_MAX
static long openmax = OPEN_MAX;
#else
static long openmax = 0;
#endif /* OPEN_MAX */

#define OPEN_MAX_GUESS 256

long open_max (void)
{
	if (openmax == 0)
	{
		errno = 0;
		if ((openmax = sysconf (_SC_OPEN_MAX)) < 0)
		{
			if (errno == 0)
				openmax = OPEN_MAX_GUESS;
			else
				wp_error_sys_exit ("sysconf error for _SC_OPEN_MAX");
		}

	}
	return (openmax);
}
