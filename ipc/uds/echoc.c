#if 0
${CC-gcc} ${CFLAGS--g -Wall} -o `basename $0 .c` $0
exit $?
#endif

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCK_PATH "/tmp/echo.socket"

int main (int argc, char *argv[])
{
	int s, t, len;
	struct sockaddr_un remote;
	char str[128];

	if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
	{
		perror ("socket");
		exit (1);
	}

	printf ("Trying to connect...\n");

	/* bind */
	remote.sun_family = AF_UNIX;
	sprintf (remote.sun_path, "%s%d", SOCK_PATH, getpid());
	unlink (remote.sun_path);
	len = strlen (remote.sun_path) + sizeof (remote.sun_family);
	if (bind (s, (struct sockaddr *)&remote, len) == -1)
	{
		perror ("bind");
		exit (1);
	}
	unlink (remote.sun_path);
	
	/* connect */
	strcpy (remote.sun_path, SOCK_PATH);
	len = strlen (remote.sun_path) + sizeof (remote.sun_family);
	if (connect (s, (struct sockaddr *)&remote, len) == -1)
	{
		perror ("connect");
		exit (1);
	}

	printf ("Connected.\n");

	while (printf ("> "), fgets (str, sizeof (str), stdin), !feof (stdin)) 
	{
		if (send (s, str, strlen (str), 0) == -1)
		{
			perror ("send");
			exit (1);
		}

		if ((t = recv (s, str, sizeof (str), 0)) > 0)
		{
			str[t] = '\0';
			printf ("echo> %s", str);
		}
		else
		{
			if (t < 0) perror ("recv");
			else printf ("Server closed connection\n");
			exit (1);
		}
	}	

	close (s);

	return 0;
}
