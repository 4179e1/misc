#include <stdio.h>
#include <assert.h>

int get_val (void)
{
	return 1;
}

int main (void)
{
	assert (get_val() > 0);

	printf ("hello world\n");

	return 0;
}
