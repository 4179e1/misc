#include "wpunixio.h"
#include "wpbase.h"

int wp_chdir (const char *pathname)
{
	int n;
	if ((n = chdir (pathname)) == -1)
		wp_error_sys_warning ("chdir error");
	return n;
}

int wp_closedir (DIR *dp)
{
	int n;
	if ((n = closedir (dp)) == -1)
		wp_error_sys_warning ("closedir error");
	return n;
}

int wp_fchdir (int filedes)
{
	int n;
	if ((n = fchdir (filedes)) == -1)
		wp_error_sys_warning ("fchdir error");
	return n;
}

char *wp_getcwd (char *buf, size_t size)
{
	char *cwd;
	if ((cwd = getcwd (buf, size)) == NULL)
		wp_error_sys_warning ("getcwd error");
	return cwd;
}

int wp_mkdir (const char *pathname, mode_t mode)
{
	int n;
	if ((n = mkdir (pathname, mode)) == -1)
		wp_error_sys_warning ("mkdir error");
	return n;
}

DIR *wp_opendir (const char *pathname)
{
	DIR *dp;
	if ((dp = opendir (pathname)) == NULL)
		wp_error_sys_warning ("opendir error");
	return dp;
}

struct dirent *wp_readdir (DIR *dp)
{
	struct dirent *dir;
	if ((dir = readdir (dp)) == NULL)
		wp_error_sys_warning ("readdir error");
	return dir;
}

int wp_rmdir (const char *pathname)
{
	int n;
	if ((n = rmdir (pathname)) == -1)
		wp_error_sys_warning ("rmdir error");
	return n;
}
