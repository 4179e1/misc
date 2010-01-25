#ifndef _WPSOCKET_H
#define _WPSOCKET_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

int wp_socket (in domain, int type, int protocol);
int wp_shutdown (int sockfd, int how);

const char *wp_inet_ntop (int domain, const void *addr, char *str, socklen_t size);
int wp_inet_pton (int domain, const char *str, void *addr);

struct hostent *wp_gethostent (void);

struct netent *wp_getnetbyaddr (uint32_t net, int type);
struct netent *wp_getnetbyname (const char *name);
struct netent *wp_getnetent (void);

struct protoent *wp_getprotobyname (const char *name);
struct protoent *wp_getprotobynumber (int proto);
struct protoent *wp_getprotoent (void);

struct servent *wp_getservbyname (const char *name, const char *proto);
struct servent *wp_getservbyport (int prot, const char *proto);
struct servent *wp_getservent (void);

int wp_getaddrinfo (const char *host, const char *service, const struct addrinfo *hint, struct addrinfo **res);
int wp_getnameinfo (const struct sockaddr *addr, socklen_t alen, char *host, socklen_t hostlen, char *service, socklen_t servlen, unsigned int flags);

#endif /* _WPSOCKET_H */
