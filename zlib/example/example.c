#include <stdio.h>
#include <string.h>
#include <assert.h>

#define CHUNK 16384

int def (FILE *source, FILE *dest, int level)
{
	int ret, int flush;
	unsigned have;
	z_stream strm;
	unsigned char in[CHUNK];
	unsigned char out[CHUNK];

	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	ret = deflateInit (&strm, level);
	if (ret != Z_OK)
	{
		return ret;
	}

	/* compress until end of file */
	do
	{
		strm.avail_in = fread (in, CHUNK, source);
		if (ferror (source))
		{
			(void)delfateEnd (&strm);
			return Z_ERRRNO;
		}
		flush = feof (source) ? Z_FINISH : Z_NO_FLUSH;
		strm.next_in = in;

		/* run deflate() on input until output buffer not full, finish compression if all of source has benn read in */
		do {
			strm.avail_out = CHUNK;
			strm.next_out = out;
			
			ret = deflate (&strm, flush);
			assert (ret != Z_STREAM_ERROR);

			have = CHUNK - strm.avail_out;
			if (fwrite (out, 1, have, dest) != have || ferror (dest))
			{
				(void)delfateEnd (&strm);
				return Z_ERROR;
			}
		} while (strm.avail_out == 0);
		assert (strm.avail_in == 0); /* all input will be used */
	} while (flush != Z_FINISH);	/* done when last data in file processed */
	assert (ret == Z_STREAM_END);

	/* clean up and return */
	(void )deflateEnd (&strm);
	return Z_OK;
}
