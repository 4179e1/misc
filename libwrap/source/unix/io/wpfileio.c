#include <fcntl.h>
#include <unistd.h>
#include <utime.h>
#include "wpunixio.h"
#include "wpbase.h"

int wp_access (const char *pathname, int mode)
{
	int n;
	if ((n = access (pathname, mode)) == -1)
		wp_error_sys_info ("access error");
	return n;
}

int wp_chmod (const char *pathname, mode_t mode)
{
	int n;
	if ((n = chmod (pathname, mode)) == -1)
		wp_error_sys_warning ("chmod error");
	return n;
}

int wp_chown (const char *pathname, uid_t owner, gid_t group)
{
	int n;
	if ((n = chown (pathname, owner, group)) == -1)
		wp_error_sys_warning ("chown error");
	return n;
}

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

int wp_fchmod (int filedes, mode_t mode)
{
	int n;
	if ((n = fchmod (filedes, mode)) == -1)
		wp_error_sys_warning ("fchmod error");
	return n;
}

int wp_fchown (int filedes, uid_t user, gid_t group)
{
	int n;
	if ((n = fchown (filedes, user, group)) == -1)
		wp_error_sys_warning ("fchown error");
	return n;
}

int wp_fcntl (int filedes, int cmd, int arg)
{
	int rt;
	if ((rt = fcntl (filedes, cmd, arg)) == -1)
		wp_error_sys_warning ("fcntl error");
	return rt;
}

int wp_fdatasync (int filedes)
{
	int rt;
	if ((rt = fdatasync (filedes)) == -1)
		wp_error_sys_warning ("fdatasync error");
	return rt;
}

int wp_fstat (int filedes, struct stat *buf)
{
	int n;
	if ((n = fstat (filedes, buf)) == -1)
		wp_error_sys_warning ("fstat error");
	return n;
}

int wp_fsync (int filedes)
{
	int n;
	if ((n = fsync (filedes)) == -1)
		wp_error_sys_warning ("fsysnc error");
	return n;
}

int ftruncate (int filedes, off_t length)
{
	int n;
	if ((n = ftruncate (filedes, length)) == -1)
		wp_error_sys_warning ("ftruncate error");
	return n;
}

off_t wp_lseek (int filedes, off_t offset, int whence)
{
	off_t pos;
	if ((pos = lseek (filedes, offset, whence)) == -1)
		wp_error_sys_warning ("lseek error");
	return pos;
}

int wp_lchown (const char *pathname, uid_t owner, gid_t group)
{
	int n;
	if ((n = lchown (pathname, owner, group)) == -1)
		wp_error_sys_warning ("lchown error");
	return n;
}

int wp_link (const char *existingpath, const char *newpath)
{
	int n;
	if ((n = link (existingpath, newpath)) == -1)
		wp_error_sys_warning ("link error");
	return n;
}

int wp_lstat (const char *pathname, struct stat *buf)
{
	int n;
	if ((n = lstat (pathname, buf)) == -1)
		wp_error_sys_warning ("lstat error");
	return n;
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

ssize_t wp_readlink (const char *pathname, char *buf, size_t bufsize)
{
	ssize_t n;
	if ((n = readlink (pathname, buf, bufsize)) == -1)
		wp_error_sys_warning ("readlink error");
	return n;
}

int wp_stat (const char *pathname, struct stat *buf)
{
	int n;
	if ((n = stat (pathname, buf)) == -1)
		wp_error_sys_warning ("stat error");
	return n;
}

int wp_symlink (const char *actualpath, const char *sympath)
{
	int n;
	if ((n = symlink (actualpath, sympath)) == -1)
		wp_error_sys_warning ("symlink error");
	return n;
}

int wp_truncate (const char *pathname, off_t length)
{
	int n;
	if ((n = truncate (pathname, length)) == -1)
		wp_error_sys_warning ("truncate error");
	return n;
}

int wp_unlink (const char *pathname)
{
	int n;
	if ((n = unlink (pathname)) == -1)
		wp_error_sys_warning ("unlink error");
	return n;
}

int wp_utime (const char *pathname, const struct utimbuf *times)
{
	int n;
	if ((n = utime (pathname, times)) == -1)
		wp_error_sys_warning ("utime error");
	return n;
}

ssize_t wp_write (int filedes, const void *buf, size_t nbytes)
{
	ssize_t n;
	if ((n = write (filedes, buf, nbytes)) == -1)
		wp_error_sys_warning ("write error");
	return n;
}
