#include <sys/wait.h>
#include <stdio.h>
#include <assert.h>

int main (int argc, char *argv[])
{
	FILE *f;
	int i;
	char buf[1024];
	
	assert (argc == 2);

	f = popen (argv[1], "r");
	assert (f != NULL);

#if 0	
	fgets (buf, sizeof (buf), f);

	if (feof (f))
	{
		printf ("no outputss\n");
	}
#endif

	i = WEXITSTATUS (pclose (f));
	printf ("exit status %d\n", i);

	return 0;
}
