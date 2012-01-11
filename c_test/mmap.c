#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mount.h>
#include <sys/mman.h>
#include <assert.h>

int main (int argc, char *argv[])
{
	int fd;
	unsigned long long size=0;
	void *ptr;
	fd = open ("/dev/lvmdatas/small", O_RDWR);
	assert (fd >= 0);

	assert (ioctl(fd, BLKGETSIZE64, &size) >= 0);
	printf ("disk size %llu\n", size);

	/* depends on memory size & disk size */
	ptr = mmap (NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);

	if (ptr == (void *)-1)
	{
		perror ("unable to map disk");
	}
	else
	{
		printf ("disk mapped\n");
		munmap (ptr, size);
	}

	close (fd);
	return 0;
}
