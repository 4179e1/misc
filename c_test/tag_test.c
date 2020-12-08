#include <stdio.h>
#include <stdbool.h>

bool id3v1_file_have_tag (FILE *file)
{
	char tmp[4];
	tmp[3] = '\0';

	if (fseek (file, -128, SEEK_END) != 0)
	{
		printf ("fseek error\n");
		return false;
	}

	fread (tmp, 3, 1, file);

	if (strncmp (tmp, "TAG", 3) == 0)
	{
		return true;
	}

	return false;
}

int main (int argc, char *argv[])
{
	if (argc != 2)
	{
		printf ("missing argv\n");
		return 1;
	}

	FILE *file = fopen (argv[1], "rb+");
	if (file == NULL)
	{
		printf ("fopen error\n");
		return 2;
	}

	if (id3v1_file_have_tag (file))
	{
		printf ("have tag\n");
	}
	else 
	{
		printf ("don't have tag\n");
	}

	fclose (file);

	return 0;
}
