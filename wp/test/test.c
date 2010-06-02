#include <libwrap.h>

int main (int argc, char *argv[])
{
	FILE *file;

	if (argc != 2)
	{
		wp_error_exit (-1, "usage: %s filename", argv[0]);
	}


	file  = wp_fopen (argv[1], "r");
	if (file)
	{
		wp_fclose (file);
	}
	else
	{
		wp_error_warning ("open %s failed", argv[0]);
	}


	return 0;
}
