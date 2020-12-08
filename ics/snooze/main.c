#include <stdio.h>
#include <libwrap.h>

void sigint_handler (int z)
{
	return;
}

unsigned int snooze (unsigned int secs)
{
	unsigned int z = sleep (secs);

	printf ("Slept for %u of %u secs.\n", secs - z, secs);

	return z;
}

int main (int argc, char *argv[])
{
	unsigned int u;

	if (argc != 2)
	{
		wp_error_exit (-1, "usage: %s seconds\n", argv[0]);
	}

	if (sscanf (argv[1], "%u", &u) != 1)
	{
		wp_error_exit (-2, "argument %s is not a digit\n", argv[1]);
	}

	wp_signal (SIGINT, sigint_handler);

	snooze (u);

	return 0;
}
