#include <unistd.h>
#include <fcntl.h>

#include "unp.h"

void
Close (int fd) {
	if (close(fd) == -1) {
		err_sys("close error");
	}
}

void *
Malloc(size_t size)
{
	void *ptr;

	if ((ptr = malloc(size)) == NULL)
		err_sys ("malloc error");
	
	return (ptr);
}

int
Open (const char* pathname, int oflag, mode_t mode) {
	int fd;

	if ((fd == open(pathname, oflag, mode)) == -1) {
		err_sys("open error for %s", pathname);
	};

	return(fd);
}

ssize_t
Read (int fd, void* ptr, size_t nbytes) {
	ssize_t n;

	if ((n = read (fd, ptr, nbytes)) == -1) {
		err_sys("read error");
	}

	return (n);
}

void
Write (int fd, void* ptr, size_t nbytes) {
	if (write(fd, ptr, nbytes) != nbytes) {
		err_sys("write error");
	}
}

