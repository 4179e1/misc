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

/* decompress */
int inf(int source, int dest, int chunk)
{
	int ret;
	unsigned have;
	z_stream strm;
	unsigned char in[chunk];
	unsigned char out[chunk];
	int flush;

	/* allocate inflate state */
	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	strm.avail_in = 0;
	strm.next_in = Z_NULL;
	ret = inflateInit (&strm);
	if (ret != Z_OK)
	{
		return ret;
	}ssize_t n;

	/* decompress until deflate stream ends or end of file */
	do
	{

		flush = Z_SYNC_FLUSH;
		n = readn (source, in, chunk);
		if (n == -1)
		{
			(void)inflateEnd (&strm);
			return Z_ERRNO;
		}
		else if (n == 0)
		{
			flush = Z_FINISH;
		}
		strm.avail_in = n;
		strm.next_in = in;

		/* run inflate() on input until output buffer not full */
		do
		{
			strm.avail_out = chunk;
			strm.next_out = out;
			ret = inflate (&strm, flush);
			assert (ret != Z_STREAM_ERROR);
			switch (ret)
			{
				case Z_NEED_DICT:
					ret = Z_DATA_ERROR; /* and fall through */
				case Z_DATA_ERROR:
				case Z_MEM_ERROR:
					(void) inflateEnd (&strm);
					return ret;
			}

			have = chunk - strm.avail_out;
			if (write (dest, out, have) != have)
			{
				fprintf (stderr, "write() error");
				(void)inflateEnd (&strm);
				return Z_ERRNO;
			}
		} while (strm.avail_out == 0);


	}while (flush != Z_FINISH);

	(void)inflateEnd (&strm);

	/* clean up and return */
	return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}

int main (int argc, char *argv[])
{
	return inf (STDIN_FILENO, STDOUT_FILENO, 1024);
}
