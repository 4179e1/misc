#include <stdio.h>
#include <string.h>
#include "matrix.h"
#include "lcs.h"

int main (void)
{
	char *s1 = "ABCBDAB";
	char *s2 = "BDCABA";
	char dest[10];
	memset (dest, 0, sizeof (dest));

	lcs_length (s1, s2);
	lcs_print (s1, s2);
	lcs_get (s1, s2, dest, sizeof(dest));
	printf ("%s\n", dest);
	
	return 0;
}
