#include <stdio.h>

int main(void)
{
	int i;
	i = rename ("/home/lyre/abc", "/home/lyre/def");

	printf ("%d\n", i);

	return 0;
}
