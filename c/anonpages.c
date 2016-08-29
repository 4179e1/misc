#if 0
${CC:=gcc} -g -Wall -o `basename $0 .c` $0
exit 0
#endif

/*
 * This snippet simulate a memory leak
 * It allocate 100Mb memory each time enter key were pressed.
 * Monitor the memory usage in:
 * # top         <==== Press 'M' key to sort by memory (RES)
 * # pmap -x <pid>
 * # grep -i anon /proc/meminfo
 *
 * Compare the difference with/without -z option
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main (int argc, char *argv[])
{
	int size = 100 * 1024 * 1024; /* 100M */
	char *p;
	int set = 0;

	printf ("My pid is %ld\n", (long)getpid());
	if (argc >= 2 && (strcmp (argv[1], "-z") == 0))
		set = 1;
	while (1)
	{
		getchar();
		p = malloc (size);
		printf ("Allocated 100M memory");
		assert (p != NULL);
		if (set)
		{
			memset(p, 'z', size);
			printf (", and filled it");
		}
		printf ("\n");
	}
}
