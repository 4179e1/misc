#ifndef _WPERROR_H
#define _WPERROR_H

/* error process */
void wp_err_msg (const char *fmt, ...);
void wp_err_ret (const char *fmt, ...);
void wp_err_exit (const char *fmt, ...);

/* error process for system call, check errno */
void wp_err_sys_msg (const char *fmt, ...);
void wp_err_sys_ret (const char *fmt, ...);
void wp_err_sys_exit (const char *fmt, ...);

void wp_syslog_on (void);
void wp_syslog_off (void);
bool wp_is_syslog_on (void);

#endif /* _WPERROR_H */
