#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include "apue.h"

int
main(int argc, char *argv[])
{
	DIR				*dp;
	struct dirent	*dirp;

	if (argc != 2)
	{
		printf("usage: ls directory_name\n");
		return -1;
	}

	if ((dp = opendir(argv[1])) == NULL)
		fprintf(stderr, "can't open %s\n", argv[1]);
	while ((dirp = readdir(dp)) != NULL)
		printf("%s\n", dirp->d_name);

	closedir(dp);
	exit(0);
}
