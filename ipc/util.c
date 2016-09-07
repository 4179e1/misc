#include "util.h"

void file_client (int readfd, int writefd)
{
	size_t len;
	ssize_t n;
	char buff[MAXLINE];

	printf ("> ");
	wp_fgets( buff, MAXLINE, stdin);
	len = strlen (buff);
	if (buff[len - 1] == '\n')
		len--;

	wp_write ( writefd, buff, len);

	while ((n = wp_read (readfd, buff, MAXLINE)) > 0)
		wp_write (STDOUT_FILENO, buff, n);
}

void file_server (int readfd, int writefd)
{
	int fd;
	ssize_t n;
	char buff[MAXLINE + 1];

	if ((n = wp_read (readfd, buff, MAXLINE)) == 0)
		wp_critical ("end-of-file while reading pathname");
	buff[n] = '\0';			/* null terminate pathname */

	if ((fd = open (buff, O_RDONLY)) < 0)
	{
		snprintf (buff + n , sizeof (buff) - n, ": can't open, %s\n", strerror (errno));
		n = strlen (buff);
		write (writefd, buff, n);
	}
	else
	{
		while ((n = wp_read (fd, buff, MAXLINE)) > 0)
			wp_write (writefd, buff, n);
		wp_close (fd);
	}
}
