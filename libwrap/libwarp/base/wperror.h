#ifndef _WPERROR_H
#define _WPERROR_H
#include <stdbool.h>

void wp_error_info (const char *fmt, ...);

/* error process */
void wp_error_warning (const char *fmt, ...);
void wp_error_return (const char *fmt, ...);
void wp_error_exit (int exit_status, const char *fmt, ...);

/* error process for system call, check errno */
void wp_error_sys_warning (const char *fmt, ...);
void wp_error_sys_return (const char *fmt, ...);
void wp_error_sys_exit (const char *fmt, ...);
void wp_error_sys_exit_ws(int exit_status, const char *fmt, ...);

void wp_error_syslog_on (void);
void wp_error_syslog_off (void);
bool wp_error_is_syslog_on (void);

FILE *wp_error_set_output_file (FILE *new_of);
FILE *wp_error_get_output_file (void);

#endif /* _WPERROR_H */
