#if 0
${CC=clang} -o `basename $0 .c` -Wall $0 `pkg-config --libs --cflags libwp0 `
exit 0
#endif

#include <libwp.h>
#include <assert.h>
#include <errno.h>
#include <stdlib.h>

#define MAXLINE 1024

#define FILE_MODE (S_IRUSR |S_IWUSR |S_IRGRP |S_IROTH)
#define SERVER_FIFO "/tmp/server.fifo"
#define CLIENT_FIFO "/tmp/client.fifo"

void server (int, int);

int main (int argc, char *argv[])
{
	int readfifo, writefifo, dummyfd, fd;
	char *ptr, buff[MAXLINE + 1], fifoname [MAXLINE];
	pid_t pid;
	ssize_t n;
	wp_rio_t *rio;

	if ((mkfifo (SERVER_FIFO, FILE_MODE) < 0) && (errno != EEXIST))
	{
		wp_critical ("can't create %s", SERVER_FIFO);
	}

	readfifo = wp_open (SERVER_FIFO, O_RDONLY, 0);
	dummyfd = wp_open (SERVER_FIFO, O_WRONLY, 0);

	rio = wp_rio_new (readfifo);
	assert (rio != NULL);

	while ((n = wp_rio_readline (rio, buff, MAXLINE)) > 0)
	{
		if (buff[n -1] == '\n')
		{
			n--;
		}
		buff[n] = '\0';

		if ((ptr = strchr (buff, ' ')) == NULL)
		{
			wp_error ("bogus request: %s", buff);
			continue;
		}
		*ptr++ = 0;
		pid = atol (buff);
		snprintf (fifoname, sizeof (fifoname), "/tmp/fifo.%ld", (long) pid);
		if (( writefifo = open (fifoname, O_WRONLY, 0)) < 0)
		{
			wp_error ("cannot open : %s", fifoname);
			continue;
		}
		if ((fd = open (ptr, O_RDONLY)) < 0)
		{
			snprintf (buff + n, sizeof (buff) - n, ": can't open, %s\n", strerror(errno));
			n = strlen (ptr);
			wp_write (writefifo, ptr, n);
			close (writefifo);
		}
		else
		{
			wp_message ("OK, %s opened", fifoname);
			while (( n = wp_read (fd, buff, MAXLINE)) > 0)
			{
				wp_write (writefifo, buff, n);
			}
			close (fd);
			close (writefifo);
		}
	}
	wp_rio_free (rio);
	exit (0);
}
