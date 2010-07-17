#include <stdio.h>

#define debug(format, ...) fprintf (stderr, format, __VA_ARGS__)

int main (void)
{
	debug ("%s : %d\n", "what's up?", 1);
	return 0;
}
