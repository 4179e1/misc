#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>

int globalbss;		// should in bss?
int globalstatic = 3;

extern void mylibfoo (void);

void mylocalfoo()
{
	int functionvar;
	printf ("variable functionvar \t location: 0x%p\n", &functionvar);
}

int main()
{
	void *localvar1= (void *)malloc (2048);
	printf ("variable globalbss \t location: 0x%p\n", &globalbss);
	printf ("variable globalstatic \t location: 0x%p\n", &globalstatic);
	printf ("variable stackvar \t location: 0x%p\n", &localvar1);
	printf ("variable heapvar \t location: 0x%p\n", localvar1);


	mylibfoo();
	mylocalfoo();

	printf ("# cat /proc/%zd/maps\n", (intmax_t) getpid());
	getchar();

	return 0;
}
