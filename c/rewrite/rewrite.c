#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	FILE *fp;
	FILE *dfp;
	fp = fopen ("test", "r");
	if (fp == NULL) {
		fprintf (stderr, "Error\n");
		exit (1);
	}

	dfp = fopen ("output", "w");
	if (dfp == NULL) {
		fprintf (stderr, "Error\n");
		exit (1);
	}

	int c;

	while ( (c = getc (fp)) != EOF ) {
		if ( c == 'a')
		{
			printf("a");
			continue;
		}
		putc (c, dfp);
	}

	fclose (fp);
	fclose (dfp);

	return 0;
}
