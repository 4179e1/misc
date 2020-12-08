#if 0
clang -Wall -o `basename $0 .c` $0
exit
#endif

static char **get_array (void)
{
	static char *array[] =
	{
		"abc",
		"def",
	};

	return array;
}

#include <stdio.h>
int main (void)
{
	char *abc[] =
	{
		"123",
		"456",
	};

	printf ("%s\n", abc[1]);
	printf ("%s\n", get_array()[1]);

	return 0;
}
