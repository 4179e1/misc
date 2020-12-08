#include <stdio.h>

int main (int argc, char *argv[])
{
	char buf[1024] = {0};

	if (argc != 2)
	{
		fprintf (stderr, "usage: %s cmd\n", argv[0]);
		return -1;
	}

	FILE *file;
	file = popen (argv[1], "r");
	if (file == NULL)
	{
		fprintf (stderr, "popen error\n");
		return -1;
	}

	while (fgets (buf, sizeof (buf), file))
	{
		printf (buf);
	}

	pclose (file);

	return 0;
}
