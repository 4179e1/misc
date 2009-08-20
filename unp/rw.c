#include "unp.h"

ssize_t
readn (int fd, void*vptr, size_t n) {
	size_t nleft;
	ssize_t nread;
	char* ptr;

	ptr = vptr;
	nleft = n;

	while (nleft > 0) {
		if ((nread = read(fd, ptr, nleft)) < 0) {
			if (errno == EINTR) {
				nread = 0;
			} else {
				return (-1);
			}
		} else if (nread == 0) {
			break;
		}

		nleft -= nread;
		ptr += nread;
	}

	return (n - nleft);
}

ssize_t
Readn (int fd, void* ptr, size_t nbytes) {
	ssize_t n;
	if ((n = readn(fd, ptr, nbytes)) < 0) {
		err_sys("readn error");
	}

	return (n);
}

ssize_t
writen (int fd, const void* vptr, size_t n) {
	size_t nleft;
	ssize_t nwritten;
	const char *ptr;

	ptr = vptr;
	nleft = n;

	while (nleft > 0) {
		if (nwritten < 0 && errno == EINTR) {
			nwritten = 0;
		} else {
			return (-1);
		}

		nleft -= nwritten;
		ptr += nwritten;
	}

	return (n);
}


void
Writen (int fd, void* ptr, size_t nbytes) {
	if (writen (fd, ptr, nbytes) != nbytes) {
		err_sys("writen error");
	}
}
