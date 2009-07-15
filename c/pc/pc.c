#include <stdio.h>
#include <stdlib.h>

#define MAXWORD 1024

void error (const char *str) {
	fprintf (stderr, "%s\n", str);
	exit (1);
}

int main (int argc, char *argv[]) {
	FILE *sfp;
	FILE *dfp;

	char tmp[MAXWORD];
	char sh[MAXWORD];

	int c;
	int i;

	if ( argc < 2 )
		error ("Usage: pc FILENAME");

	for ( i = 1; i < argc; i ++ )
	{
		sfp = fopen (argv[i], "r");
		if ( NULL == sfp )
			error ("Can NOT open source file");

		sprintf (tmp, ".%s~", argv[i]);

		dfp = fopen (tmp, "w");
		if (NULL == dfp)
			error ("Can NOT open destination file");

		while ((c = getc (sfp)) != EOF )
		{
			if ( ';' == c )
			{
				fputs (" {\n\n}\n", dfp);
				continue;
			}

			fputc (c, dfp);
		}

		fclose (sfp);
		fclose (dfp);

		sprintf (sh, "mv %s %s", tmp, argv[i]);
		remove (argv[i]);
		system (sh);
	}

	return 0;
}
