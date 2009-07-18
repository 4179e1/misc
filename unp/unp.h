#ifndef _UNP_H
#define _UNP_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define MAXLINE 4096

/**
 * error
 */
void err_ret 	(const char* fmt, ...);
void err_sys 	(const char* fmt, ...);
void err_dump 	(const char* fmt, ...);
void err_msg 	(const char* fmt, ...);
void err_quit 	(const char* fmt, ...);

/**
 * wrapsock
 */
int Accept (int fd, struct sockaddr *sa, socklen_t *salenptr);
void Bind (int fd, const struct sockaddr *sa, socklen_t salen);
void Connect (int fd, const struct sockaddr *sa, socklen_t salen);
void Listen (int fd, int backlog);
int Socket (int family, int type, int protocol);

/**
 * wrapunix
 */
void Close (int fd);
int Open (const char* pathname, int oflag, mode_t mode);
ssize_t Read (int fd, void* ptr, size_t nbytes);
void Write (int fd, void* ptr, size_t nbytes);
#endif /* _UNP_H */
