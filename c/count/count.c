#include <stdio.h>

int get_rows (const char *filename)
{
	int count = 0;
	int c;

	FILE *fp;

	if (NULL == (fp = fopen(filename, "r")))
	{
		fprintf(stderr, "can't open %s\n", filename);
		return -1;
	}

	while ((c = getc (fp)) != EOF)
	{
		if ( '\n' == c )
			count++;
	}

	if (fclose (fp) != 0)
	{
		fprintf (stderr, "fclose() fail\n");
		return -1;
	}

	return count;
}


int main(int argc, char *argv[])
{
	int num ;
	int count;
	int fileno = 0;
	int totle = 0;

	if (argc < 2)
	{
		fprintf (stderr, "Usage: prog FILENAME\n");
		return -1;
	}


	for (num = 1; num < argc; num++)
	{
		count = get_rows(argv[num]);

		printf ("%d\t%s\n", count, argv[num]);
		totle += count;
		fileno ++;
	}

	printf("\n%d lines totle in %d files, average %d lines in a file\n", totle, fileno, (totle / fileno));

	return 0;
}
