#ifndef _WPBASE_H
#define _WPBASE_H

#define WP_BUF_SIZE 1024

#include <stdio.h>
#include <stdbool.h>

/*****************
 * error
 ****************/
void wp_error_info (const char *fmt, ...);

/* error process */
void wp_error_warning (const char *fmt, ...);
void wp_error_return (const char *fmt, ...);
void wp_error_exit (int exit_status, const char *fmt, ...);

/* error process for system call, check errno */
void wp_error_sys_info (const char *fmt, ...);
void wp_error_sys_warning (const char *fmt, ...);
void wp_error_sys_return (const char *fmt, ...);
void wp_error_sys_exit (const char *fmt, ...);
void wp_error_sys_exit_with_status (int exit_status, const char *fmt, ...);

void wp_error_syslog_on (void);
void wp_error_syslog_off (void);
bool wp_error_is_syslog_on (void);

FILE *wp_error_set_output_file (FILE *new_of);
FILE *wp_error_get_output_file (void);

/************************************************
 * path
 ***********************************************/
int wp_get_path_size(void);
char *wp_path_alloc(int *sizep);

/***********************************************
 * openmax
 **********************************************/
long open_max (void);

#endif /* _WPBASE_H */
