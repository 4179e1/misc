#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>


int main (int argc, char *argv[])
{
	int fd;
	char buf[4096];

	if ((argc >= 2) && (strcmp (argv[1], "-n") == 0))
	{
		readlink ("ln", buf, sizeof (buf));
		printf ("%s",  buf);
		printf ("\n");
		return 0;
	}
	else
	{	
		fd = open ("ln", O_RDWR);
	}
	assert (fd != -1);

	while (read (fd, buf, sizeof (buf)) > 0)
	{
		printf ("%s",  buf);
	}

	return 0;
}

