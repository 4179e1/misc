/**
 * @mainpage
 * @brief this document contain comment of librio
 * 		librio is an example package to illustrate
 *		the usage of autoconf & doxygen. It originally
 *		came from CS:APP.
 */

/**
 * @file 
 * @brief the Robust I/O Library from CS:APP.
 */

#ifndef _LIBRIO_H
#define _LIBRIO_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup rio Rio module
 * @{
 */

/**
 * @brief read n bytes from fd, and store it in ptr.
 * @param fd the file-descriptor to read.
 * @param ptr the buffer to store the result.
 * @param n bytes to read
 * @return The actually readed bytes.
 *			or -1 if fail.
 */
ssize_t rio_readn (int fd, void *ptr, size_t n);

/**
 * @brief write n bytes in ptr to fd.
 * @param fd the file-descriptor to write.
 * @param ptr the buffer hold the datas to write
 * @param n bytes to write
 * @return The actually written bytes.
 *			or -1 if fail.
 */
ssize_t rio_writen (int fd, void *ptr, size_t n);

/**
 * @typedef Rio
 * @brief the rio struct.
 */
typedef struct _rio Rio;

/**
 * @brief create a new Rio.
 * @param fd the file-descriptor to read/write.
 * @return The newly allocated Rio, or NULL if failed.
 *			Use rio_free() to deallocate it.
 * @see rio_free()
 */
Rio *rio_new (int fd);
/**
 * @brief deacllocate a Rio.
 * @param rp th rio created by rio_new()
 * @see rio_new()
 */
void rio_free (Rio* rp);

/**
 * @brief read a line from rp into usrbuf, whose size is maxlen.
 			that is after encounter a '\\n', this funcition shall return.
 * @param rp the Rio the read.
 * @param usrbuf buffer to store the result.
 * @param maxlen size of buffer
 * @return the acctually readed size. or -1 if failed.
 * @see rio_new()
 * @see rio_free()
 */
ssize_t rio_readlineb (Rio *rp, void *usrbuf, size_t maxlen);

/**
 * @brief read n bytes from rp to userbuf.
 * @param rp the rio to read.
 * @param usrbuf buffer to store the result.
 * @param n size to read
 * @return the acctually readed size. or -1 if failed.
 * @see rio_new()
 * @see rio_free()
 */
ssize_t rio_readnb (Rio *rp, void *usrbuf, size_t n);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _LIBRIO_H */
