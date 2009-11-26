#include <fcntl.h>
#include <unistd.h>
#include "wpunixio.h"
#include "../../base/wpbase.h"

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

#if defined __USE_BSD || defined __USE_XOPEN_EXTENDED
int wp_fchmod (int filedes, mode_t mode)
{
	int n;
	if ((n = fchmod (filedes, mode)) == -1)
		wp_error_sys_warning ("fchmod error");
	return n;
}
#endif /* __USE_BSD || defined __USE_XOPEN_EXTENDED */

#if defined __USE_BSD || defined __USE_XOPEN_EXTENDED
int wp_fchown (int filedes, uid_t user, gid_t group)
{
	int n;
	if ((n = fchown (filedes, user, group)) == -1)
		wp_error_sys_warning ("fchown error");
	return n;
}
#endif /* __USE_BSD || defined __USE_XOPEN_EXTENDED */

int wp_fcntl (int filedes, int cmd, int arg)
{
	int rt;
	if ((rt = fcntl (filedes, cmd, arg)) == -1)
		wp_error_sys_warning ("fcntl error");
	return rt;
}

#if defined __USE_POSIX199309 || defined __USE_UNIX98
int wp_fdatasync (int filedes)
{
	int rt;
	if ((rt = fdatasync (filedes)) == -1)
		wp_error_sys_warning ("fdatasync error");
	return rt;
}
#endif /* __USE_POSIX199309 */

int wp_fstat (int filedes, struct stat *buf)
{
	int n;
	if ((n = fstat (filedes, buf)) == -1)
		wp_error_sys_warning ("fstat error");
	return n;
}

#if defined __USE_BSD || defined __USE_XOPEN || defined __USE_XOPEN2K
int wp_fsync (int filedes)
{
	int n;
	if ((n = fsync (filedes)) == -1)
		wp_error_sys_warning ("fsysnc error");
	return n;
}
#endif /* Use BSD || X/Open || Unix98.  */

#if defined __USE_BSD || defined __USE_XOPEN_EXTENDED
int ftruncate (int filedes, off_t length)
{
	int n;
	if ((n = ftuncate (filedes, length)) == -1)
		wp_error_sys_warning ("ftruncate error");
	return n;
}
#endif /* __USE_BSD || defined __USE_XOPEN_EXTENDED */

off_t wp_lseek (int filedes, off_t offset, int whence)
{
	off_t pos;
	if ((pos = lseek (filedes, offset, whence)) == -1)
		wp_error_sys_warning ("lseek error");
	return pos;
}

#if defined __USE_BSD || defined __USE_XOPEN_EXTENDED
int wp_lchown (const char *pathname, uid_t owner, gid_t group)
{
	int n;
	if ((n = lchown (pathname, owner, group)) == -1)
		wp_error_sys_warning ("lchown error");
	return n;
}
#endif /* Use BSD || X/Open Unix.  */

#if defined __USE_BSD || defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K
int wp_lstat (const char *restrict pathname, struct stat *restrict buf)
{
	int n;
	if ((n = lstat (pathname, buf)) == -1)
		wp_error_sys_warning ("lstat error");
	return n;
}
#endif /* __USE_BSD || defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K */

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

int wp_stat (const char *restrict pathname, struct stat *restrict buf)
{
	int n;
	if ((n = stat (pathname, buf)) == -1)
		wp_error_sys_warning ("stat error");
	return n;
}

#if defined __USE_BSD || defined __USE_XOPEN_EXTENDED
int wp_truncate (const char *pathname, off_t length)
{
	int n;
	if ((n = truncate (pathname, length)) == -1)
		wp_error_sys_warning ("truncate error");
	return n;
}
#endif /* __USE_BSD || defined __USE_XOPEN_EXTENDED */

ssize_t wp_write (int filedes, const void *buf, size_t nbytes)
{
	ssize_t n;
	if ((n = write (filedes, buf, nbytes)) == -1)
		wp_error_sys_warning ("write error");
	return n;
}
