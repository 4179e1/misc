#include <libwp.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "lib.h"
int main (int argc, char *argv[])
{
	int i, j, fd, nchildren, nloops, nbytes;
	pid_t pid;
	ssize_t n;
	char request[MAXLINE], reply[MAXN];
	if (argc != 6)
		wp_critical ("usage: client <hostname or IP> <port> <#children> "
					"<#loops/child> <#bytes/request>");
	nchildren = atoi (argv[3]);
	nloops = atoi (argv[4]);
	nbytes = atoi (argv[5]);	
	
	snprintf (request, sizeof(request), "%d\n", nbytes);

	for (i = 0; i < nchildren; i++)
	{
		if ((pid = wp_fork()) == 0)
		{
			for (j = 0; j < nloops; j ++)
			{
				fd = wp_open_clientfd (argv[1], atoi(argv[2]));
				n = wp_write (fd, request, strlen (request));
				wp_debug ("%d bytes written\n", n);
				wp_debug ("going to read %d bytes\n", nbytes);
				if ((n = wp_readn (fd, reply, nbytes)) != nbytes)
					wp_critical ("server returned %d bytes", n);
				wp_close(fd);
			}
			wp_message ("child %d done\n", i);
			exit (0);
		}
		/* parent loops around to fork() again */
	}

	while (wait (NULL) > 0)
		;

	if (errno != ECHILD)
		wp_critical ("wait() error %d", errno);
	return 0;
}
