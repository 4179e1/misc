#include "util.h"

void mylock (int fd);
void myunlock (int fd);

#define SEQFILE "seqno"
int main (int argc, char *argv[])
{
	int fd;
	long i, seqno;
	pid_t	pid;
	ssize_t n;
	char line[MAXLINE + 1];

	pid = getpid();
	fd = wp_open (SEQFILE, O_RDWR, FILE_MODE);
	for (i = 0; i < 20; i++)
	{
		mylock(fd);
		wp_lseek (fd, 0L, SEEK_SET);
		n = wp_read (fd, line, MAXLINE);
		line[n] = '\0';

		n = sscanf (line, "%ld\n", &seqno);
		printf ("%s: pid = %ld, seq = %ld\n", argv[0], (long) pid, seqno);
		seqno++;
		snprintf (line, sizeof (line), "%ld\n", seqno);
		wp_lseek (fd, 0L, SEEK_SET);
		wp_write (fd, line, strlen(line));
		
		myunlock (fd);
	}

	return 0;
}

#ifdef NOLOCK
void mylock (int fd)
{
	return;
}

void myunlock (int fd)
{
	return;
}
#else
void mylock (int fd)
{
	struct flock lock = 
	{
		.l_type = F_WRLCK,
		.l_whence = SEEK_SET,
		.l_start = 0,
		.l_len = 0,
	};
	if (fcntl (fd, F_SETLKW, &lock) != 0)
		wp_critical ("fcntl() failed: %s", strerror (errno));
}

void myunlock (int fd)
{
	struct flock lock = 
	{
		.l_type = F_UNLCK,
		.l_whence = SEEK_SET,
		.l_start = 0,
		.l_len = 0,
	};

	if (fcntl (fd, F_SETLK, &lock) != 0)
		wp_critical ("fcntl() failed: %s", strerror (errno));
}
#endif /* NOLOCK */
