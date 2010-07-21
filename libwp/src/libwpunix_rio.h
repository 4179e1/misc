#ifndef _LIBWPUNIX_RIO_H
#define _LIBWPUNIX_RIO_H

ssize_t wp_readn (int fd, void *ptr, size_t n);
ssize_t wp_writen (int fd, void *ptr, size_t n);

#endif /*_LIBWPUNIX_RIO_H */
