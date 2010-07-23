#ifndef _LIBWPUNIX_RIO_H
#define _LIBWPUNIX_RIO_H

ssize_t wp_readn (int fd, void *ptr, size_t n);
ssize_t wp_writen (int fd, void *ptr, size_t n);

typedef struct _rio Rio;

Rio *wp_rio_new (int fd);
void wp_rio_free (Rio* rp);

ssize_t wp_rio_readlineb (Rio *rp, void *usrbuf, size_t maxlen);
ssize_t wp_rio_readnb (Rio *rp, void *usrbuf, size_t n);

#endif /*_LIBWPUNIX_RIO_H */
