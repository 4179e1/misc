#ifndef _WPUNIXIO_H
#define _WPUNIXIO_H

#include <stdio.h>
#include <limits.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <dirent.h>
#include <utime.h>

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

int wp_fchmod (int filedes, mode_t mode);
int wp_fchown (int filedes, uid_t user, gid_t group);
int wp_fcntl (int filedes, int cmd, int arg);
int wp_fdatasync (int filedes);
int wp_fstat (int filedes, struct stat *buf);
int wp_fsync (int filedes);
int wp_ftruncate (int filedes, off_t length);
int wp_ioctl (int filedes, int request, void *arg);
off_t wp_lseek (int filedes, off_t offset, int whence);
int wp_lchown (const char *pathname, uid_t owenr, gid_t group);
int wp_link (const char *exsitingpath, const char *newpath);
int wp_lstat (const char *pathname, struct stat *buf);
int wp_open (const char *pathname, int oflag, mode_t mode);
ssize_t wp_read (int filedes, void *buf, size_t nbytes);
ssize_t wp_readlink (const char *pathname, char *bug, size_t bufsize);
int wp_stat (const char *pathname, struct stat *buf);
int wp_symlink (const char *actualpath, const char *sympath);
int wp_truncate (const char *pathname, off_t length);
int wp_unlink (const char *pathname);
int wp_utime (const char *pathname, const struct utimbuf *times);
ssize_t wp_write (int filedes, const void *buf, size_t nbytes);

/**************************************
 * wp io utilities
 *************************************/
int wp_fd_create (const char *pathname, mode_t mode);
int wp_fd_alloc (const char *pathname, mode_t mode, off_t offset);
int wp_fd_append (int filedes, off_t offset);

void wp_fd_set_flag (int fd, int flags);
void wp_fd_clear_flag (int fd, int flags);
bool wp_fd_is_flag_set (int fd, int flag);

typedef void (*wp_dopath_func) (const char *path, void *data);
void wp_dopath (char *path, wp_dopath_func func, void *data);

/**************************************
 * wp file utilities
 *************************************/
int wp_chdir (const char *pathname);
int wp_closedir (DIR *dp);
int wp_fchdir (int filedes);

char *wp_getcwd (char *bug, size_t size);
int wp_mkdir (const char *pathname, mode_t mode);
DIR *wp_opendir (const char *pathname);
struct dirent *wp_readdir (DIR *dp);
int wp_rmdir (const char *pathname);
#endif /* _WPUNIXIO_H */
