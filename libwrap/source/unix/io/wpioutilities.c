#include <string.h>
#include "wpunixio.h"
#include "wpbase.h"

int wp_fd_create (const char *pathname, mode_t mode)
{
	return wp_open (pathname, O_RDWR | O_CREAT | O_TRUNC, mode);
}

int wp_fd_alloc (const char *pathname, mode_t mode, off_t offset)
{
	int fd;
	fd = wp_open (pathname, O_RDWR | O_CREAT | O_TRUNC, mode);
	wp_lseek (fd, offset, SEEK_SET);
	return fd;
}

int wp_fd_append (int filedes, off_t offset)
{
	wp_lseek (filedes, offset, SEEK_CUR);
	return filedes;
}

void wp_fd_set_flag (int fd, int flags)
{
	int val;

	val = wp_fcntl (fd, F_GETFL, 0);
	val |= flags;
	wp_fcntl (fd, F_SETFL, val);
}

void wp_fd_clear_flag (int fd, int flags)
{
	int val;

	val = wp_fcntl (fd, F_GETFL, 0);
	val &= ~flags;
	wp_fcntl (fd, F_SETFL, val);
}

bool wp_fd_is_flag_set (int fd, int flag)
{
	int val;

	val = wp_fcntl (fd, F_GETFL, 0);
	return (val & flag);
}

void wp_dopath (char *path, wp_dopath_func func, void *data)
{
	struct stat statbuf;
	struct dirent *dirp;
	DIR *dp;
	char *ptr;

	if (wp_lstat (path, &statbuf) == -1)
		return;
	if (S_ISDIR (statbuf.st_mode) == 0)
		func (path, data);

	ptr = path + strlen (path);
	*ptr++ = '/';
	*ptr = 0;

	if ((dp = wp_opendir (path)) == NULL)
		return;

	while ((dirp = readdir (dp)) != NULL)
	{
		if (strcmp (dirp->d_name, ".") == 0 || 
				strcmp (dirp->d_name, "..") == 0)
			continue;

		strcpy (ptr, dirp->d_name);
		wp_dopath (path, func, data);
	}

	ptr[-1] = 0;

	wp_closedir (dp);
}
