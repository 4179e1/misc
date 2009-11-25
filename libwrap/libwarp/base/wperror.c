#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <syslog.h>
#include <errno.h>
#include "wpbase.h"

#define EXIT_STATUS_DEFAULT -1

static bool wp_syslog_status = false;
static FILE *wp_error_of = NULL;

static void error_do (bool errnoflag, int level, const char *fmt, va_list ap);

void wp_error_info (const char *fmt, ...)
{
	va_list ap;

	va_start (ap, fmt);
	error_do (false, LOG_INFO, fmt, ap);
	va_end (ap);
}

void wp_error_warning (const char *fmt, ...)
{
	va_list ap;
	
	va_start (ap, fmt);
	error_do (false, LOG_WARNING, fmt, ap);
	va_end (ap);
}

void wp_error_return (const char *fmt, ...)
{
	va_list ap;

	va_start (ap, fmt);
	error_do (false, LOG_ERR, fmt, ap);
	va_end (ap);

	return;
}

void wp_error_exit (int exit_status, const char *fmt, ...)
{
	va_list ap;

	va_start (ap, fmt);
	error_do (false, LOG_ERR, fmt, ap);
	va_end (ap);
	
	exit (exit_status);
}

void wp_sys_warning (const char *fmt, ...)
{
	va_list ap;
	
	va_start (ap, fmt);
	error_do (true, LOG_WARNING, fmt, ap);
	va_end (ap);
}

void wp_error_sys_return (const char *fmt, ...)
{
	va_list ap;

	va_start (ap, fmt);
	error_do (true, LOG_ERR, fmt, ap);
	va_end (ap);

	return;
}

void wp_error_sys_exit (const char *fmt, ...)
{
	va_list ap;

	va_start (ap, fmt);
	error_do (true, LOG_ERR, fmt, ap);
	va_end (ap);
	
	exit (EXIT_STATUS_DEFAULT);
}

void wp_error_sys_exit_with_status (int exit_status, const char *fmt, ...)
{
	va_list ap;

	va_start (ap, fmt);
	error_do (true, LOG_ERR, fmt, ap);
	va_end (ap);

	exit (exit_status);
}

void wp_error_syslog_on (void) 
{
	wp_syslog_status = true;
}

void wp_error_syslog_off (void)
{
	wp_syslog_status = false;
}

bool wp_error_is_syslog_on (void)
{
	return wp_syslog_status;
}

FILE *wp_error_set_output_file (FILE *new_of)
{
	wp_error_of = new_of;
	return wp_error_of;
}

FILE *wp_error_get_output_file (void)
{
	return wp_error_of;
}


static void error_do (bool errnoflag, int level, const char *fmt, va_list ap)
{
	int errno_save;
	int n;
	char buf[WP_BUF_SIZE];

	errno_save = errno;

	vsnprintf (buf, WP_BUF_SIZE, fmt, ap);

	n = strlen (buf);
	if (errnoflag)
		snprintf (buf + n, (WP_BUF_SIZE - n), ": %s", strerror (errno_save));
	strcat (buf, "\n");

	if (wp_syslog_status) 
	{
		syslog (level, buf);
	}
	else 
	{
		fflush (stdout);
		fputs (buf, ((wp_error_of == NULL) ? stderr : wp_error_of));
		fflush (stderr);
	}

	return;
}
