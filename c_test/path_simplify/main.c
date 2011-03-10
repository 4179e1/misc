#include <assert.h>
#include <stdio.h>

/* Remove "/../", "//", "/./" parts from path.
 *
 * /blah/..         gets  /
 * /blah/../foo     gets  /foo
 * /abc/./xyz       gets  /abc/xyz
 * /abc//xyz        gets  /abc/xyz
 *
 * NOTE: src and dest can point to the same buffer, in which case,
 *       the operation is performed in-place.
 */
int buffer_path_simplify(char *dest, char *src)
{
	int toklen;
	char c, pre1;
	char *start, *slash, *walk, *out;
	unsigned short pre;

	if (src == NULL || dest == NULL)
		return -1;

	walk  = src;
	start = dest;
	out   = dest;
	slash = dest;

	while (*walk == ' ') {
		walk++;
	}

	pre1 = *(walk++);
	c    = *(walk++);
	pre  = pre1;
	if (pre1 != '/') {
		pre = ('/' << 8) | pre1; 
		*(out++) = '/';
	}
	*(out++) = pre1;

	if (pre1 == '\0') {
		return 0;
	}

	while (1) {
		if (c == '/' || c == '\0') {
			toklen = out - slash;
			if (toklen == 3 && pre == (('.' << 8) | '.')) {
				out = slash;
				if (out > start) {
					out--;
					while (out > start && *out != '/') {
						out--;
					}
				}

				if (c == '\0')
					out++;
			} else if (toklen == 1 || pre == (('/' << 8) | '.')) {
				out = slash;
				if (c == '\0')
					out++;
			}

			slash = out;
		}

		if (c == '\0')
			break;

		pre1 = c;
		pre  = (pre << 8) | pre1;
		c    = *walk;
		*out = pre1;

		out++;
		walk++;
	}

	*out = '\0';

	return 0;
}

int main (int argc, char *argv[])
{
	assert (argc == 2);
	char buf[1024] = {0};

	buffer_path_simplify (buf, argv[1]);

	printf ("%s\n", buf);
	
	return 0;
}
