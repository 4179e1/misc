#include <fcntl.h>
#include <unistd.h>
#include "wpunixio.h"
#include "../../base/wpbase.h"

int wp_close (int filedes)
{
	int rt;
	if ((rt = close (filedes)) == -1)
		wp_error_sys_warning ("close error");
	return rt;
}

int wp_creat (const char *pathname, mode_t mode)
{
	int fd;
	if ( (fd = creat (pathname, mode)) == -1)
		wp_error_sys_warning ("creat %s error");
	return fd;
}

int wp_dup (int filedes)
{
	int fd;
	if ((fd = dup (filedes)) == -1)
		wp_error_sys_warning ("dup error");
	return fd;
}

int wp_dup2 (int filedes, int filedes2)
{
	int fd;
	if ((fd = dup2 (filedes, filedes2)) == -1)
		wp_error_sys_warning ("dup2 error");
	return fd;
}

int wp_fdatasync (int filedes)
{
	int rt;
	if ((rt = fdatasync (filedes)) == -1)
		wp_error_sys_warning ("fdatasync error");
	return rt;
}

int wp_fcntl (int filedes, int cmd, int arg)
{
	int rt;
	if ((rt = fcntl (filedes, cmd, arg)) == -1)
		wp_error_sys_warning ("fcntl error");
	return rt;
}

int wp_fsync (int filedes);
off_t wp_lseek (int filedes, off_t offset, int whence)
{
	off_t pos;
	if ((pos = lseek (filedes, offset, whence)) == -1)
		wp_error_sys_warning ("lseek error");
	return pos;
}

int wp_ioctl (int filedes, int request, void *arg)
{
	int rt;
	if ((rt = ioctl (filedes, request, arg)) == -1)
		wp_error_sys_warning ("ioctl error");
	return rt;
}

int wp_open (const char *pathname, int oflag, mode_t mode)
{
	int fd;
	if ((fd = open (pathname, oflag, mode)) == -1)
		wp_error_sys_warning ("open %s error", pathname);
	return fd;
}

ssize_t wp_read (int filedes, void *buf, size_t nbytes)
{
	ssize_t n;
	if ((n = read (filedes, buf, nbytes)) == -1)
		wp_error_sys_warning ("read error");
	return n;
}
