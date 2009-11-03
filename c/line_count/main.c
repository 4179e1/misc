#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXLINE 1024

static char fullpath_line[MAXLINE];
static int files = 0;
static int rows = 0;

static int get_rows (const char *filename)
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

static bool identify (const char *path){
	int len = strlen(path);

	if (len >= 2)
	{
		const char *ptr = (path + len - 2);
		if (strcmp (ptr, ".c") == 0 || strcmp (ptr, ".h") == 0)
		{
			return true;
		}

		if (len >= 4)
		{
			ptr-=2;
			if (strcmp (ptr, ".cpp") == 0)
			{
				return true;
			}
		}
	}

	return false;
}

static void listfile (char* fullpath)
{
	struct stat statbuf;
	struct dirent *dir;
	DIR *dp;
	char *ptr;
	int len;


	if (lstat(fullpath, &statbuf) < 0)
	{
		fprintf (stderr, "lstat() error\n");
		return;
	}

	if (S_ISDIR(statbuf.st_mode) == 0)
	{
		//fprintf (stderr, "\"%s\" not a directory\n", fullpath);
		if (identify (fullpath))
		{
			if ((len = get_rows (fullpath)) >= 0)
			{
				printf ("%d\t%s\n", len, fullpath);
				files++;
				rows += len;
			}
		}
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
		fprintf (stderr, "usage: count <path>\n");
		exit (1);
	}

	int i;
	for (i = 0; i < sizeof(fullpath); i++)
	{
		fullpath[i] = '\0';
	}

	strcpy (fullpath, argv[1]);

	listfile(fullpath_line);

	printf ("\n%d lines in %d files, average %d linse in a file\n",
			rows, files, (files == 0 ? 0 : (rows/files)));

	return 0;
}
