#if 0
${CC-gcc} ${CFLAGS--g -Wall} -o `basename $0 .c` $0
exit $?
#endif

/*
 * taken from http://beej.us/guide/bgipc/output/html/multipage/unixsock.html
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <signal.h>


#define SOCK_PATH "/tmp/echo.socket"

void sigchld_handler (int sig)
{
	while (waitpid (-1, 0, WNOHANG) > 0)
		;
	return;
}

int main (int argc, char *argv[])
{
	int s, c, len;
	struct sockaddr_un local, remote;
	char str[128];

	if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
	{
		perror ("socket");
		exit (1);
	}

	local.sun_family = AF_UNIX;
	strcpy (local.sun_path, SOCK_PATH);
	unlink (local.sun_path);
	len = strlen (local.sun_path) + sizeof (local.sun_family);
	if (bind(s, (struct sockaddr *)&local, len) == -1)
	{
		perror ("bind");
		exit (1);
	}

	if (listen (s, 5) == -1)
	{
		perror ("listen");
		exit (1);
	}

	if (signal (SIGCHLD, sigchld_handler) == SIG_ERR)
	{
		perror ("signal");
		exit (1);
	}

	while (1) {

		int done, n;
		socklen_t t;
		pid_t p;

		printf ("Waiting for a connection...\n");
		t = sizeof (remote);
		if ((c = accept (s, (struct sockaddr *)&remote, &t)) == -1)
		{
			perror ("accept");
			exit (1);
		}

		/* parent */
		if ((p = fork ()) > 0 )
		{
			close (c);	
		}
		/* child */
		else if (p == 0)
		{
			close (s);
			printf ("Connected to %s.\n", remote.sun_path);
			done = 0;

			do {
				n = recv (c, str, sizeof (str), 0);
				if (n <= 0) 
				{
					if (n < 0) perror ("recv");
					done = 1;
				}

				if (!done)
					if (send (c, str, n, 0) < 0) 
					{
						perror ("send");
						done = 1;
					}
			} while (!done);

			close (c);
			exit (0);
		}
		else
		{
			perror ("fork");
			exit (1);
		}

	}

	return 0;
}
