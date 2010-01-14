#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void wp_check_exit_status (int status)
{
	if (WIFEXITED (status))
		printf ("normal termination, exit status = %d\n", WEXITSTATUS(status));
	else if (WIFSIGNALED (status))
		printf ("abnormal termination, signal number = %d%s\n", WTERMSIG(status), 
#ifdef WCOREDUMP
				WCOREDUMP (status) ? "core file generated" : ""
#else
				""
#endif
			   );
	else if (WIFSTOPPED (status))
		printf ("child stopped, signal number = %d\n", WSTOPSIG (status));
}

ssize_t wp_readn (int fd, void *ptr, size_t n)
{
	size_t nleft;
	ssize_t nread;

	nleft = n;
	while (nleft >0)
	{
		if ((nread = read (fd, ptr, nleft)) < 0)
		{
			if (nleft == n)
			{
				return -1; /* error, return -1 */
			}
			else
			{
				break;		/* error, return amout read so far */
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
	size_t nleft;
	size_t nwritten;

	nleft = n;
	while (n > 0)
	{
		if ((nwritten = write (fd, ptr, nleft)) < 0)
		{
			if (nleft == n)
			{
				return -1;
			}
			else
			{
				break;
			}
		}
		else if (nwritten == 0)
		{
			break;
		}

		nleft -= nwritten;
		ptr += nwritten;
	}

	return (n - nleft);
}
