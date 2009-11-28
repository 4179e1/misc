#ifndef _WPUNIXIO_H
#define _WPUNIXIO_H

#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

/***************************************
 * wp file io
 **************************************/

int wp_access (const char *pathname, int mode);
int wp_chmod (const char *pathname, mode_t mode);
int wp_chown (const char *pathname, uid_t owner, gid_t group);
int wp_close (int filedes);
int wp_creat (const char *pathname, mode_t mode);
int wp_dup (int filedes);
int wp_dup2 (int filedes, int filedes2);

#if defined __USE_BSD || defined __USE_XOPEN_EXTENDED
int wp_fchmod (int filedes, mode_t mode);
#endif /* __USE_BSD || defined __USE_XOPEN_EXTENDED */

#if defined __USE_BSD || defined __USE_XOPEN_EXTENDED
int wp_fchown (int filedes, uid_t user, gid_t group);
#endif /* __USE_BSD || defined __USE_XOPEN_EXTENDED */

int wp_fcntl (int filedes, int cmd, int arg);

#if defined __USE_POSIX199309 || defined __USE_UNIX98
int wp_fdatasync (int filedes);
#endif /* __USE_POSIX199309 */

int wp_fstat (int filedes, struct stat *buf);

#if defined __USE_BSD || defined __USE_XOPEN || defined __USE_XOPEN2K
int wp_fsync (int filedes);
#endif /* Use BSD || X/Open || Unix98.  */

#if defined __USE_BSD || defined __USE_XOPEN_EXTENDED
int wp_ftruncate (int filedes, off_t length);
#endif /* __USE_BSD || defined __USE_XOPEN_EXTENDED */

int wp_ioctl (int filedes, int request, void *arg);
off_t wp_lseek (int filedes, off_t offset, int whence);

#if defined __USE_BSD || defined __USE_XOPEN_EXTENDED
int wp_lchown (const char *pathname, uid_t owenr, gid_t group);
#endif /* Use BSD || X/Open Unix.  */

#if defined __USE_BSD || defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K
int wp_lstat (const char *restrict pathname, struct stat *restrict buf);
#endif /* __USE_BSD || defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K */

int wp_open (const char *pathname, int oflag, mode_t mode);
ssize_t wp_read (int filedes, void *buf, size_t nbytes);
int wp_stat (const char *restrict pathname, struct stat *restrict buf);

#if defined __USE_BSD || defined __USE_XOPEN_EXTENDED
int wp_truncate (const char *pathname, off_t length);
#endif /* __USE_BSD || defined __USE_XOPEN_EXTENDED */

ssize_t wp_write (int filedes, const void *buf, size_t nbytes);

/**************************************
 * wp file utilities
 *************************************/
int wp_fd_create (const char *pathname, mode_t mode);
int wp_fd_alloc (const char *pathname, mode_t mode, off_t offset);
int wp_fd_append (int filedes, off_t offset);

void wp_fd_set_flag (int fd, int flags);
void wp_fd_clear_flag (int fd, int flags);
bool wp_fd_is_flag_set (int fd, int flag);

#endif /* _WPUNIXIO_H */
