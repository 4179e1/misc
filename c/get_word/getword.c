#include <stdio.h>
#include <ctype.h>

#define MAXWORD 100
#define MAXLENGTH 100

int get_word (char *word[], const char *filename,  int lim)
{
	FILE *fp;
	int c;
	int count = 0;

	if (NULL == (fp = fopen (filename, "r")))
	{
		fclose (fp);
		fprintf (stderr, "can't open %s\n", filename);
		return -1;
	}

	while ((c = getc (fp)) != EOF )
	{
		if ( isspace (c))
		{
			putchar ('\n');
			continue;
		}
		putchar (c);
	}

}

int main(int argc, char *argv[])
{
	int num;
	int i;

	char *word[MAXWORD];
	if (argc < 2)
	{
		printf ("USAGE: PROG FILENAME\n");
		return -1;
	}

	num = get_word (word, argv[1], MAXLENGTH);

	if (num > 0)
	{
		for (i = 0; i < num; i++)
			printf("%s\n", word[i]);
	}

	return 0;
}
