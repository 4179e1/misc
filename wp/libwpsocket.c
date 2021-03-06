#include "libwpsocket.h"
#include "libwpbase.h"

int wp_socket (int domain, int type, int protocol)
{
	int n;
	if ((n = socket (domain, type, protocol)) == -1)
		wp_warning ("socket() error");
	return n;
}

int wp_shutdown (int sockfd, int how)
{
	int n;
	if ((n = shutdown (sockfd, how)) == -1)
		wp_warning ("shutdown() error");
	return n;
}

const char *wp_inet_ntop (int domain, const void *addr, char *str, socklen_t size)
{
	const char *p;
	if ((p = inet_ntop (domain, addr, str, size)) == NULL)
		wp_warning ("inet_ntop() error");
	return p;
}

int wp_inet_pton (int domain, const char *str, void *addr)
{
	int n;
	if ((n = inet_pton (domain, str, addr)) == -1)
		wp_warning ("inet_pton() error");
	else if (n == 0)
		wp_warning ("inet_pton() error: invalid format \"%s\"", str);
	return n;
}

struct hostent *wp_gethostent (void)
{
	struct hostent *p;
	if ((p = gethostent ()) == NULL)
		wp_warning ("gethostent() error");
	return p;
}

struct netent *wp_getnetbyaddr (uint32_t net, int type)
{
	struct netent *p;
	if ((p = getnetbyaddr (net, type)) == NULL)
		wp_warning ("getnetbyaddr() error");
	return p;
}

struct netent *wp_getnetbyname (const char *name)
{
	struct netent *p;
	if ((p = getnetbyname (name)) == NULL)
		wp_warning ("getnetbyname() error");
	return p;
}

struct netent *wp_getnetent (void)
{
	struct netent *p;
	if ((p = getnetent ()) == NULL)
		wp_warning ("getnetent() error");
	return p;
}

struct protoent *wp_getprotobyname (const char *name)
{
	struct protoent *p;
	if ((p = getprotobyname (name)) == NULL)
		wp_warning ("getprotobyname() error");
	return p;
}

struct protoent *wp_getprotobynumber (int proto)
{
	struct protoent *p;
	if ((p = getprotobynumber (proto)) == NULL)
		wp_warning ("getprotobynumber() error");
	return p;
}

struct protoent *wp_getprotoent (void)
{
	struct protoent *p;
	if ((p = getprotoent ()) == NULL)
		wp_warning ("getprotoent() error");
	return p;
}

struct servent *wp_getservbyname (const char *name, const char *proto)
{
	struct servent *p;
	if ((p = getservbyname (name, proto)) == NULL)
		wp_warning ("getservbyname() error");
	return p;
}

struct servent *wp_getservbyport (int prot, const char *proto)
{
	struct servent *p;
	if ((p = getservbyport (prot, proto)) == NULL)
		wp_warning ("getservbyport() error");
	return p;
}

struct servent *wp_getservent (void)
{
	struct servent *p;
	if ((p = getservent ()) == NULL)
		wp_warning ("getservent() error");
	return p;
}

int wp_getaddrinfo (const char *host, const char *service, const struct addrinfo *hint, struct addrinfo **res)
{
	int n;
	if ((n = getaddrinfo (host, service, hint, res)) != 0)
		wp_warning ("getaddrinfo() error: %s", gai_strerror (n));
	return n;
}

int wp_getnameinfo (const struct sockaddr *addr, socklen_t alen, char *host, socklen_t hostlen, char *service, socklen_t servlen, unsigned int flags)
{
	int n;
	if ((n = getnameinfo (addr, alen, host, hostlen, service, servlen, flags)) != 0)
		wp_warning ("getnameinfo() error: %s", gai_strerror (n));
	return n;
}

int wp_bind (int sockfd, const struct sockaddr *addr, socklen_t len)
{
	int n;
	if ((n = bind (sockfd, addr, len)) == -1)
		wp_warning ("bind() error");
	return n;
}

int wp_getsockname (int sockfd, struct sockaddr *addr, socklen_t *alenp)
{
	int n;
	if ((n = getsockname (sockfd, addr, alenp)) == -1)
		wp_warning ("getsockname() error");
	return n;
}

int wp_getpeername (int sockfd, struct sockaddr *addr, socklen_t *alenp)
{
	int n;
	if ((n = getpeername (sockfd, addr, alenp)) == -1)
		wp_warning ("getpeername() error");
	return n;
}

int wp_connect (int sockfd, const struct sockaddr *addr, socklen_t len)
{
	int n;
	if ((n = connect (sockfd, addr, len)) == -1)
		wp_warning ("connect() error");
	return n;
}

int wp_listen (int sockfd, int backlog)
{
	int n;
	if ((n = listen (sockfd, backlog)) == -1)
		wp_warning ("listen() error");
	return n;
}

int wp_accept (int sockfd, struct sockaddr *addr, socklen_t *len)
{
	int n;
	if ((n = accept (sockfd, addr, len)) == -1)
		wp_warning ("accept() error");
	return n;
}

ssize_t wp_send (int sockfd, const void *buf, size_t nbytes, int flags)
{
	ssize_t n;
	if ((n = send (sockfd, buf, nbytes, flags)) == -1)
		wp_warning ("send() error");
	return n;
}

ssize_t wp_sendto (int sockfd, const void *buf, size_t nbytes, int flags, const struct sockaddr *destaddr, socklen_t destlen)
{
	ssize_t n;
	if ((n = sendto (sockfd, buf, nbytes, flags, destaddr, destlen)) == -1)
		wp_warning ("sendto() error");
	return n;
}

ssize_t wp_sendmsg (int sockfd, const struct msghdr *msg, int flags)
{
	ssize_t n;
	if ((n = sendmsg (sockfd, msg, flags)) == -1)
		wp_warning ("sendmsg() error");
	return n;
}

ssize_t wp_recv (int sockfd, void *buf, size_t nbytes, int flags)
{
	ssize_t n;
	if ((n = recv (sockfd, buf, nbytes, flags)) == -1)
		wp_warning ("recv() error");
	return n;
}

ssize_t wp_recvfrom (int sockfd, void *buf, size_t len, int flags, struct sockaddr *addr, socklen_t *addrlen)
{
	ssize_t n;
	if ((n = recvfrom (sockfd, buf, len, flags, addr, addrlen)) == -1)
		wp_warning ("recvfrom() error");
	return n;
}

ssize_t wp_recvmsg (int sockfd, struct msghdr *msg, int flags)
{
	ssize_t n;
	if ((n = recvmsg (sockfd, msg, flags)) == -1)
		wp_warning ("recvmsg() error");
	return n;
}

int wp_setsockopt (int sockfd, int level, int option, const void *val, socklen_t len)
{
	int n;
	if ((n = setsockopt (sockfd, level, option, val, len)) == -1)
		wp_warning ("setsockopt() error");
	return n;
}

int wp_getsockopt (int sockfd, int level, int option, void *val, socklen_t *lenp)
{
	int n;
	if ((n = getsockopt (sockfd, level, option, val, lenp)) == -1)
		wp_warning ("getsockopt() error");
	return n;
}

int wp_sockatmark (int sockfd)
{
	int n;
	if ((n = sockatmark (sockfd)) == -1)
		wp_warning ("sockatmark() error");
	return n;
}
