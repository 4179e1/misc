#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINE 4096

static char fullpath[MAXLINE];
static char new_name[MAXLINE];

static void rucs (const char *path)
{
	int i = 0;
	int len = strlen (path);
	const char *ptr = path;

	while (*ptr != '\0')
	{
		if (isascii(*ptr))
		{
			new_name[i] = *ptr;
			i++;
		}
		ptr++;
	}
	new_name[i] = '\0';

	if (i == len)
		return;

	printf ("renameing %s to %s\n", fullpath, new_name);
	rename (fullpath, new_name);

}

static void listfile (const char* path)
{
	struct stat statbuf;
	struct dirent *dir;
	DIR *dp;
	char *ptr;


	if (lstat(path, &statbuf) < 0)
	{
		fprintf (stderr, "lstat() error\n");
		return;
	}

	if (S_ISDIR(statbuf.st_mode) == 0)
	{
		//fprintf (stderr, "\"%s\" not a directory\n", fullpath);

		rucs (fullpath);
		return;
	}

	ptr = fullpath + strlen(fullpath);
	*ptr++ = '/';
	*ptr = 0;

	//printf ("listing contents in \"%s\"\n", fullpath);

	if ((dp = opendir(fullpath)) == NULL)
	{
		fprintf (stderr, "opendir(\"%s\") error\n", fullpath);
		return;
	}

	while ((dir = readdir(dp)) != NULL)
	{
		if(strcmp (dir->d_name, ".") == 0 || 
		   strcmp (dir->d_name, "..") == 0)
		{
			continue;
		}

		strcpy (ptr, dir->d_name);
		//printf ("%s\n", fullpath);
		listfile (fullpath);
	}

	ptr[-1] = 0;

	if (closedir (dp) < 0)
	{
		fprintf (stderr, "can't close directory %s\n", fullpath);
		return;
	}
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf (stderr, "usage: rucs <path>\n");
		exit (1);
	}

	int i;
	for (i = 0; i < sizeof(fullpath); i++)
	{
		fullpath[i] = '\0';
		new_name[i] = '\0';
	}

	strcpy (fullpath, argv[1]);

	listfile(fullpath);

	return 0;
}
