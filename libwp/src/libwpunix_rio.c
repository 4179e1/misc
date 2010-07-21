#include "libwpunix.h"
#include <errno.h>
#include <unistd.h>

ssize_t wp_readn (int fd, void *ptr, size_t n)
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
				wp_sys_func_warning ();
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

ssize_t wp_writen (int fd, void *ptr, size_t n)
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

