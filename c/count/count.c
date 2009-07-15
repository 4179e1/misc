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

	return count;
}


int main(int argc, char *argv[])
{
	int num ;
	int count;
	int totle = 0;

	if (argc < 2)
	{
		fprintf (stderr, "Usage: prog FILENAME\n");
		return -1;
	}


	for (num = 1; num < argc; num++)
	{
		count = get_rows(argv[num]);

		if (count > 0)
		{
			printf ("%d\t%s\n", count, argv[num]);
			totle += count;
		}
	}

	printf("\n%d\tlines totle\n", totle);

	return 0;
}
