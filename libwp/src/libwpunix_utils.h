#ifndef _LIBWPUNIX_UTILS_H
#define _LIBWPUNIX_UTILS_H

#include <sys/time.h>

void wp_check_exit_status (int status);

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

/*************************************
 * wp timer utilities
 ************************************/

typedef struct timeval WpTimer;

WpTimer *wp_timer_new ();
void wp_timer_free (WpTimer *t);
void wp_timer_start (WpTimer *t);
double wp_timer_elapse (WpTimer *t);

#endif /*_LIBWPUNIX_UTILS_H */
