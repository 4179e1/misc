#include <stdio.h>
#include <unistd.h>

int main (void)
{
	printf ("%d\n", getdtablesize());
	return 0;
}
