#ifndef _UNP_H
#define _UNP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <poll.h>

#define MAXLINE 4096
#define BUFFSIZE 8192
#define LISTENQ 1024

#define SERV_PORT 9877
#define SERV_PORT_STR "9877"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

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
void Getpeername (int fd, struct sockaddr *sa, socklen_t *salenptr);
void Getsockname (int fd, struct sockaddr *sa, socklen_t *salenptr);
void Getsockopt (int sockfd, int level, int optname, void *optval, socklen_t *optlen);
void Listen (int fd, int backlog);
int Poll (struct pollfd *fdarray, unsigned long nfds, int timeout);
ssize_t Recvfrom (int fd, void *ptr, size_t nbytes, int flags, struct sockaddr *sa, socklen_t *salenptr);
int Select (int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
void Sendto (int fd, const void *ptr, size_t nbytes, int flags, const struct sockaddr *sa, socklen_t salen);
int Socket (int family, int type, int protocol);
void Setsockopt (int sockfd, int level, int optname, void *optval, socklen_t optlen);
void Shutdown (int fd, int how);

/**
 * wrapunix
 */
void Close (int fd);
void *Malloc (size_t);
int Open (const char* pathname, int oflag, mode_t mode);
ssize_t Read (int fd, void* ptr, size_t nbytes);
void Write (int fd, void* ptr, size_t nbytes);

/**
 * wraplib
 */
const char* Inet_ntop (int family, const void* addrptr, char* strptr, size_t len);
void Inet_pton (int family, const char* strptr, void* addrptr);
#endif /* _UNP_H */

/**
 * wrapstdio
 */
char* Fgets (char* ptr, int n, FILE* stream);
void Fputs (const char* ptr, FILE* stream);


/**
 * str
 */
void str_echo(int sockfd);
void str_cli (FILE* fp, int sockfd);


/**
 * rw
 */
ssize_t Readn (int fd, void* ptr, size_t nbytes);
void Writen (int fd, void* ptr, size_t nbytes);
ssize_t Readline (int fd, void* ptr, size_t maxlen);


/**
 * signal
 */
typedef void Sigfunc(int);
Sigfunc* Signal (int signo, Sigfunc* func);

/**
 * sock
 */
char *Sock_ntop (const struct sockaddr *sa, socklen_t salen);
