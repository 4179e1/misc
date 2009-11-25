#ifndef _WPUNIXIO_H
#define _WPUNIXIO_H

#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

/***************************************
 * wpfileio
 **************************************/
int wp_close (int filedes);
int wp_creat (const char *pathname, mode_t mode);
int wp_dup (int filedes);
int wp_dup2 (int filedes, int filedes2);
int wp_fdatasync (int filedes);
int wp_fcntl (int filedes, int cmd, int arg);
int wp_fsync (int filedes);
int wp_ioctl (int filedes, int request, void *arg);
off_t wp_lseek (int filedes, off_t offset, int whence);
int wp_open (const char *pathname, int oflag, mode_t mode);
ssize_t wp_read (int filedes, void *buf, size_t nbytes);

/**************************************
 * wpfileutilities
 *************************************/
int wp_fd_create (const char *pathname, mode_t mode);
int wp_fd_alloc (const char *pathname, mode_t mode, off_t offset);
int wp_fd_append (int filedes, off_t offset);

void wp_fd_set_flag (int fd, int flags);
void wp_fd_clear_flag (int fd, int flags);
bool wp_fd_is_flag_set (int fd, int flag);

#endif /* _WPUNIXIO_H */
