#include <stdio.h>
#include <assert.h>

int main (int argc, char *argv[])
{
	FILE *f;
	char buf[1024];
	
	assert (argc == 2);

	f = popen (argv[1], "r");
	assert (f != NULL);

	fgets (buf, sizeof (buf), f);

	if (feof (f))
	{
		printf ("no outputss\n");
	}

	fclose (f);

	return 0;
}
