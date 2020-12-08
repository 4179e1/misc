/* commet */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <unistd.h>
#include "librio.h"

#define RIO_BUFSIZE 8192

/**
 * structure of rio
 */
struct _rio
{
	int rio_fd;		/**< file descriptor to manipulte */
	int rio_cnt;	/**< unread bytes */
	char *rio_bufptr;  /**< current byte */
	char rio_buf[RIO_BUFSIZE]; /**< buffer */
};

static ssize_t rio_read (Rio *rp, char *usrbuf, size_t n);

ssize_t rio_readn (int fd, void *ptr, size_t n)
{
	size_t nleft = n;
	ssize_t nread;

	while (nleft >0)
	{
		if ((nread = read (fd, ptr, nleft)) < 0)
		{
			if (errno == EINTR)
			{
				nread = 0;
			}
			else
			{
				fprintf (stderr, "read() error: %s\n", strerror (errno));
				return -1;
			}
		}
		else if (nread == 0)
		{
			break; /* EOF */
		}
		nleft -= nread;
		ptr += nread;
	}

	return (n - nleft);
}

ssize_t rio_writen (int fd, void *ptr, size_t n)
{
	size_t nleft = n;
	size_t nwritten;

	while (nleft > 0)
	{
		if ((nwritten = write (fd, ptr, nleft)) < 0)
		{
			if (errno == EINTR)
			{
				nwritten = 0;
			}
			else
			{
				return -1;
			}
		}
		nleft -= nwritten;
		ptr += nwritten;
	}

	return n;
}


Rio *rio_new (int fd)
{
	Rio *rp = malloc (sizeof (Rio));
	if (rp == NULL)
		return NULL;

	rp->rio_fd = fd;
	rp->rio_cnt = 0;
	rp->rio_bufptr = rp->rio_buf;

	return rp;
}

void rio_free (Rio* rp)
{
	assert (rp != NULL);
	free (rp);
}

static ssize_t rio_read (Rio *rp, char *usrbuf, size_t n)
{
	int cnt;

	while (rp->rio_cnt <= 0)
	{
		rp->rio_cnt = wp_read (rp->rio_fd, rp->rio_buf, sizeof (rp->rio_buf));
		if (rp->rio_cnt < 0)
		{
			if (errno != EINTR)
			{
				return -1;
			}
		}
		else if (rp->rio_cnt == 0)
		{
			return 0;	/* EOF */
		}
		else
		{
			rp->rio_bufptr = rp->rio_buf;
		}
	}

	cnt = n;
	if (rp->rio_cnt < n)
		cnt = rp->rio_cnt;

	memcpy (usrbuf, rp->rio_bufptr, cnt);
	rp->rio_bufptr += cnt;
	rp->rio_cnt -= cnt;

	return cnt;
}

ssize_t rio_readlineb (Rio *rp, void *usrbuf, size_t maxlen)
{
	int n, rc;
	char c;
	char *bufp = usrbuf;

	for (n = 1; n < maxlen; n++)
	{
		if ((rc = rio_read (rp, &c, 1)) == 1)
		{
			*bufp++ = c;
			if (c == '\n')
				break;
		}
		else if (rc == 0)
		{
			if (n == 1)
				return 0;	/* EOF, no data read */
			else 
				break;		/* EOF, some data read */
		}
		else
			return -1;
	}

	*bufp = 0;
	return n;
}

ssize_t rio_readnb (Rio *rp, void *usrbuf, size_t n)
{
	size_t nleft = n;
	ssize_t nread;
	char *bufp = usrbuf;

	while (nleft > 0)
	{
		if ((nread = rio_read (rp, bufp, nleft)) < 0)
		{
			if (errno == EINTR)
				nread = 0;
			else
				return -1;
		}
		else if (nread == 0)
			break;
		nleft -= nread;
		bufp += nread;
	}

	return (n - nleft);
}

