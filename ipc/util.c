#include "util.h"

void file_client (int readfd, int writefd)
{
	size_t len;
	ssize_t n;
	char buff[MAXLINE];

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



ssize_t msg_send (int fd, Mymsg *mptr)
{
	return (write(fd, mptr, MSGHDRSIZE + mptr->msg_len));
}

ssize_t msg_recv (int fd, Mymsg *mptr)
{
	size_t len;
	ssize_t n;

	if ((n = wp_read (fd, mptr, MSGHDRSIZE)) == 0)
		return (0);	/* EOF */
	else if (n != MSGHDRSIZE)
		wp_critical ("message header: expected %d, got %d", MSGHDRSIZE, n);
	
	if ((len = mptr->msg_len) > 0)
		if ((n = wp_read (fd, mptr->msg_data, len)) != len)
			wp_critical ("message data: expected %d, got %d", len, n);
	
	return len;
}


void file_client_mymsg (int readfd, int writefd)
{
	size_t len;
	ssize_t n;
	Mymsg msg;

	wp_fgets (msg.msg_data, MAXMSGDATA, stdin);
	len = strlen (msg.msg_data);
	if (msg.msg_data[len - 1] == '\n')
		len--;
	msg.msg_len = len;
	msg.msg_type = 1;

	msg_send (writefd, &msg);
	while ((n = msg_recv (readfd, &msg)) > 0)
		write (STDOUT_FILENO, msg.msg_data, n);
}

void file_server_mymsg (int readfd, int writefd)
{
	FILE *fp;
	ssize_t n;
	Mymsg msg;

	msg.msg_type = 1;
	if ((n = msg_recv (readfd, &msg)) == 0)
		wp_critical ("pathname missing");
	msg.msg_data[n] = '\0';

	if ((fp = wp_fopen (msg.msg_data, "r")) == NULL)
	{
		snprintf (msg.msg_data + n, sizeof (msg.msg_data) - n, ": can't open, %s\n", strerror(errno));
		msg.msg_len = strlen (msg.msg_data);
		msg_send (writefd, &msg);
	}
	else
	{
		while ( (n = wp_fread (msg.msg_data, 1, MAXMSGDATA, fp)) != 0)
		{
			msg.msg_len = n;
			msg_send (writefd, &msg);
		}
		wp_fclose (fp);
	}

	/* send a 0-length message to signify the end */
	msg.msg_len = 0; 
	msg_send (writefd, &msg);
	
}

Sigfunc_rt signal_rt (int signo, Sigfunc_rt func, sigset_t *mask)
{
	struct sigaction act, oact;

	act.sa_sigaction = func;
	act.sa_mask = *mask;
	act.sa_flags = SA_SIGINFO;
	if (signo == SIGALRM)
	{
#ifdef SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;
#endif /* SA_INTERRUPT */
	} else {
#ifdef SA_RESTART
		act.sa_flags |= SA_RESTART;
#endif /* SA_RESTART */
	}

	if (sigaction (signo, &act, &oact) < 0)
	{
		wp_warning ("sigaction() failed: %s", strerror (errno));
		return ((Sigfunc_rt) SIG_ERR);
	}

	return (oact.sa_sigaction);
}

void
sleep_us(unsigned int nusecs)
{
	struct timeval	tval;

	for ( ; ; ) {
		tval.tv_sec = nusecs / 1000000;
		tval.tv_usec = nusecs % 1000000;
		if (select(0, NULL, NULL, NULL, &tval) == 0)
			break;		/* all OK */
		/*
		 * Note than on an interrupted system call (i.e, SIGIO) there's not
		 * much we can do, since the timeval{} isn't updated with the time
		 * remaining.  We could obtain the clock time before the call, and
		 * then obtain the clock time here, subtracting them to determine
		 * how long select() blocked before it was interrupted, but that
		 * seems like too much work :-)
		 */
		if (errno == EINTR)
			continue;
		wp_critical ("sleep_us: select error");
	}
}
