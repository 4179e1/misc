#include "wperror.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

static char buf[1024];
static bool wp_syslog_status;

void wp_syslog_on (void) 
{
	wp_syslog_status = TRUE;
}

void wp_syslog_off (void)
{
	wp_syslog_statu = FALSE;
}

bool wp_is_syslog_on (void)
{
	return wp_syslog_status;
}
