#include "util.h"

int main (int argc, char *argv[])
{
	int readfifo, writefifo;
	size_t len;
	ssize_t n;
	char *ptr, fifoname[MAXLINE], buff[MAXLINE];
	pid_t pid;
	
	pid = getpid();
	snprintf (fifoname, sizeof (fifoname), "/tmp/fifo.%ld", (long)pid);
	if ((wp_mkfifo (fifoname, FILE_MODE)) < 0)
		wp_critical ("can't create %s", fifoname);

	snprintf (buff, sizeof (buff), "%ld ", (long)pid);
	len = strlen (buff);
	ptr = buff + len;

	wp_fgets (ptr, MAXLINE - len, stdin);
	len = strlen (buff);

	writefifo = wp_open (SERV_FIFO, O_WRONLY, 0);
	wp_write (writefifo, buff, len);

	readfifo = wp_open (fifoname, O_RDONLY, 0);
	while ((n = wp_read (readfifo, buff, MAXLINE)) > 0)
		write (STDOUT_FILENO, buff, n);
	wp_close (readfifo);
	wp_unlink (fifoname);
	exit (0);
}
