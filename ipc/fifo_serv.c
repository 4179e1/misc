#include "util.h"

int main (int argc, char *argv[])
{
	int readfifo, writefifo, dummyfd, fd;
	char *ptr, buff[MAXLINE + 1], fifoname[MAXLINE];
	pid_t pid;
	ssize_t n;

	if ((wp_mkfifo (SERV_FIFO, FILE_MODE) < 0) && (errno != EEXIST))
		wp_critical ("can't create %s", SERV_FIFO);
	
	readfifo = wp_open (SERV_FIFO, O_RDONLY, 0);
	dummyfd = wp_open (SERV_FIFO, O_WRONLY, 0); /* to prevent EOF on FIFO */

	/*
	 * the input format should looks like:
	 * client PID + <space> + pathname
	 */
	while (( n = wp_readline (readfifo, buff, MAXLINE)) > 0)
	{
		if (buff[n-1] == '\n')
			n--;
		buff[n] = '\0';

		wp_debug ("Request: %s", buff);
		if ((ptr = strchr (buff, ' ')) == NULL)
		{
			wp_warning ("bogus request: %s", buff);
			continue;
		}

		*ptr++ = 0;
		pid = atol (buff);
		snprintf (fifoname, sizeof (fifoname), "/tmp/fifo.%ld", (long)pid);
		if ((writefifo = wp_open (fifoname, O_WRONLY, 0)) < 0)
		{
			wp_warning ("cannot open: %s", fifoname);
			continue;
		}

		wp_debug ("Opening '%s'", ptr);
		if ((fd = wp_open (ptr, O_RDONLY, 0)) < 0)
		{
			snprintf (buff + n, sizeof (buff) - n, ": can't open, %s\n", strerror(errno));
			n = strlen (ptr);
			wp_write (writefifo, ptr, n);
			wp_close (writefifo);
		}
		else
		{
			while ((n = wp_read (fd, buff, MAXLINE)) > 0)
				wp_write (writefifo, buff, n);
			wp_close (fd);
			wp_close (writefifo);
		}
	}

	wp_close (dummyfd);
}
