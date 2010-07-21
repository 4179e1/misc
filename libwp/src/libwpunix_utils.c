#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/wait.h>
#include "libwpunix.h"
#include "libwpbase.h"
#include "libwpstdc.h"

void wp_check_exit_status (int status)
{
	if (WIFEXITED (status))
		printf ("normal termination, exit status = %d\n", WEXITSTATUS(status));
	else if (WIFSIGNALED (status))
		printf ("abnormal termination, signal number = %d%s\n", WTERMSIG(status), 
#ifdef WCOREDUMP
				WCOREDUMP (status) ? "core file generated" : ""
#else
				""
#endif
			   );
	else if (WIFSTOPPED (status))
		printf ("child stopped, signal number = %d\n", WSTOPSIG (status));
}

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

WpTimer *wp_timer_new ()
{
	return (WpTimer *)wp_malloc (sizeof (WpTimer));
}

void wp_timer_free (WpTimer *t)
{
	assert (t != NULL);
	free (t);
}


void wp_timer_start (WpTimer *t)
{
	assert (t != NULL);
	gettimeofday (t, NULL);
}

double wp_timer_elapse (WpTimer *t)
{
	struct timeval tfinish;
	long sec, usec;

	assert (t != NULL);

	gettimeofday (&tfinish, NULL);
	sec = tfinish.tv_sec - t->tv_sec;
	usec = tfinish.tv_usec - t->tv_usec;
	return sec + 1e-6*usec;
}
