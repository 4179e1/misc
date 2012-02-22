#if 0
gcc -g -Wall -o `basename $0 .c` $0 -lz
exit 0
#endif
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <zlib.h>

ssize_t readn (int fd, void *ptr, size_t n)
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
				fprintf (stderr, "readn() error\n");
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

/* compress */
int def (int source, int dest, int level, int chunk)
{
	int ret;
	unsigned have;
	z_stream strm;
	unsigned char in[chunk];
	unsigned char out[chunk];
	ssize_t n;
	int flush;

	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	ret = deflateInit (&strm, level);
	if (ret != Z_OK)
	{
		return ret;
	}

	flush = Z_SYNC_FLUSH;
	/* compress until end of file */
	do
	{
		n = readn (source, in, chunk);
		if (n == -1)
		{
			(void)deflateEnd (&strm);
			return Z_ERRNO;
		}
		else if (n == 0)
		{
			flush = Z_FINISH;
		}

		strm.avail_in = n;
		strm.next_in = in;

		/* run deflate() on input until output buffer not full, finish compression if all of source has benn read in */
		do {
			strm.avail_out = chunk;
			strm.next_out = out;
			
			ret = deflate (&strm, flush);
			assert (ret != Z_STREAM_ERROR);

			have = chunk - strm.avail_out;
			if (write (dest, out, have) != have)
			{
				fprintf (stderr, "write() error");
				(void)deflateEnd (&strm);
				return Z_ERRNO;
			}

		} while (strm.avail_out == 0);
		assert (strm.avail_in == 0); /* all input will be used */

	} while (n != 0);	/* done when last data in file processed */
	assert (ret == Z_STREAM_END);

	(void )deflateEnd (&strm);

	/* clean up and return */
	return Z_OK;
}

int main (int argc, char *argv[])
{

	return def (STDIN_FILENO, STDOUT_FILENO, 6, 1024);
}

