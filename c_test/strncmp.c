#include <string.h>
#include <stdio.h>

int main (void)
{
	char *s1 = "abc";
	char *s2 = "abcdefg";

	int i = strncmp (s1, s2, strlen(s2));

	printf ("%d\n", i);

	return 0;
}
