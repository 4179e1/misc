#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <libwp.h>
#include "lib.h"

/* readline taken from unp, to make life easier */
ssize_t
readline(int fd, void *vptr, size_t maxlen)
{
    ssize_t n, rc;
    char    c, *ptr;

    ptr = vptr;
    for (n = 1; n < maxlen; n++) {
      again:
        if ( (rc = read(fd, &c, 1)) == 1) {
            *ptr++ = c;
            if (c == '\n')
                break;          /* newline is stored, like fgets() */
        } else if (rc == 0) {
            *ptr = 0;
            return (n - 1);     /* EOF, n - 1 bytes were read */
        } else {
            if (errno == EINTR)
                goto again;
            return (-1);        /* error, errno set by read() */
        }
    }

    *ptr = 0;                   /* null terminate like fgets() */
    return (n);
}

void sig_int (int signo)
{
	void pr_cpu_time (void);
	pr_cpu_time();
	exit (0);
}

void sig_chld (int signo) 
{
	pid_t pid;
	int stat;

	while ( (pid = waitpid (-1, &stat, WNOHANG)) > 0) 
		wp_debug ("child %d terminated\n", pid);
	return;
}

void pr_cpu_time (void)
{
	double user, sys;
	struct rusage myusage, childusage;
	if (getrusage (RUSAGE_SELF, &myusage) < 0)
		wp_critical ("getrusage() error");

	if (getrusage (RUSAGE_CHILDREN, &childusage) < 0)
		wp_critical ("getrusage() error");
	
	user = (double) myusage.ru_utime.tv_sec + myusage.ru_utime.tv_usec/1000000.0;
	user += (double) childusage.ru_utime.tv_sec + childusage.ru_utime.tv_usec/1000000.0;
	sys = (double) myusage.ru_stime.tv_sec + myusage.ru_stime.tv_usec/1000000.0;
	sys += (double) childusage.ru_stime.tv_sec + childusage.ru_stime.tv_usec/1000000.0;

	wp_message ("user time = %g, systime = %g\n", user, sys);
}


void web_child (int sockfd)
{
	int ntowrite;
	ssize_t n;
	ssize_t nread;
	char line[MAXLINE], result[MAXN];
	memset (result, 'z', MAXN);
	while (1)
	{
		if ((nread= wp_readline (sockfd, line, MAXLINE)) == 0)
			return;
		ntowrite = atol (line);
		if ((ntowrite <= 0) || (ntowrite > MAXN))
			wp_critical ("client request for %d bytes", ntowrite);
	    n =	wp_writen (sockfd, result, ntowrite);
		wp_debug ("%d bytes written\n", n);
	}
}
