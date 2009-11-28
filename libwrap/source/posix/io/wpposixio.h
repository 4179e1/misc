#ifndef _WPPOSIXIO_H
#define _WPPOSIXIO_H

/************************************
 * wpfileio
 ***********************************/

#ifdef __USE_UNIX98
/* aton operate, lseek and read/write */
ssize_t wp_pread (int filedes, void *buf, size_t nbytes, off_t offset);
ssize_t wp_pwrite (int filedes, void *but, size_t nbytes, off_t offset);
#endif /* __USE_UNIX98 */

#endif /* _WPPOSIXIO_H */
