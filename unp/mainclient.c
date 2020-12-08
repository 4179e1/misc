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

int main (int argc, char *argv[])
{
	int readfifo, writefifo;
	size_t len;
	ssize_t n;
	char *ptr, fifoname[MAXLINE], buff[MAXLINE];
	pid_t pid;

	pid = getpid();
	snprintf (fifoname, sizeof (fifoname), "/tmp/fifo.%ld", (long)pid);
	if ((mkfifo (fifoname, FILE_MODE) < 0) && (errno != EEXIST))
	{
		wp_critical ("can't create %s", fifoname);
	}

	snprintf (buff, sizeof (buff), "%ld ", (long) pid);
	len = strlen (buff);
	ptr =  buff + len;

	wp_fgets (ptr, MAXLINE - len, stdin);
	len = strlen (buff);
	writefifo = open (SERVER_FIFO, O_WRONLY, 0);
	wp_write (writefifo, buff, len);
	readfifo = wp_open (fifoname, O_RDONLY, 0);
	while ((n = read (readfifo, buff, MAXLINE)) > 0)
	{
		wp_write (STDOUT_FILENO, buff, n);
	}

	wp_close (readfifo);
	wp_unlink (fifoname);
	exit (0);
}
