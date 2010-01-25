#include "wpsocket.h"
#include "wpbase.h"

int wp_socket (in domain, int type, int protocol)
{
	int n;
	if ((n = sockent (domain, type, protocol)) == -1)
		wp_error_warning ("socket() error");
	return n;
}

int wp_shutdown (int sockfd, int how)
{
	int n;
	if ((n = shutdown (sockfd, how)) == -1)
		wp_error_warning ("shutdown() error");
	return n;
}

const char *wp_inet_ntop (int domain, const void *addr, char *str, socklen_t size)
{
	const char *p;
	if ((p = inet_ntop (domain, addr, str, size)) == NULL)
		wp_error_warning ("inet_ntop() error");
	return p;
}

int wp_inet_pton (int domain, const char *str, void *addr)
{
	int n;
	if ((n = inet_pton (domain, str, addr)) == -1)
		wp_error_warning ("inet_pton() error");
	else if (n == 0)
		wp_error_warning ("inet_pton() error: invalid format \"%s\"", str);
	return n;
}

struct hostent *wp_gethostent (void)
{
	struct hostent *p;
	if ((p = gethostent ()) == NULL)
		wp_error_warning ("gethostent() error");
	return p;
}

struct netent *wp_getnetbyaddr (uint32_t net, int type)
{
	struct netent *p;
	if ((p = getnetbyaddr (net, type)) == NULL)
		wp_error_warning ("getnetbyaddr() error");
	return p;
}

struct netent *wp_getnetbyname (const char *name)
{
	struct netent *p;
	if ((p = getnetbyname (name)) == NULL)
		wp_error_warning ("getnetbyname() error");
	return p;
}

struct netent *wp_getnetent (void)
{
	struct netent *p;
	if ((p = getnetent ()) == NULL)
		wp_error_warning ("getnetent() error");
	return p;
}

struct protoent *wp_getprotobyname (const char *name)
{
	struct protoent *p;
	if ((p = getprotobyname (name)) == NULL)
		wp_error_warning ("getprotobyname() error");
	return p;
}

struct protoent *wp_getprotobynumber (int proto)
{
	struct protoent *p;
	if ((p = getprotobynumber (proto)) == NULL)
		wp_error_warning ("getprotobynumber() error");
	return p;
}

struct protoent *wp_getprotoent (void)
{
	struct protoent *p;
	if ((p = getprotoent ()) == NULL)
		wp_error_warning ("getprotoent() error");
	return p;
}

struct servent *wp_getservbyname (const char *name, const char *proto)
{
	struct servent *p;
	if ((p = getservbyname (name, proto)) == NULL)
		wp_error_warning ("getservbyname() error");
	return p;
}

struct servent *wp_getservbyport (int prot, const char *proto)
{
	struct servent *p;
	if ((p = getservbyport (prot, proto)) == NULL)
		wp_error_warning ("getservbyport() error");
	return p;
}

struct servent *wp_getservent (void)
{
	struct servent *p;
	if ((p = getservent ()) == NULL)
		wp_error_warning ("getservent() error");
	return p;
}

int wp_getaddrinfo (const char *host, const char *service, const struct addrinfo *hint, struct addrinfo **res)
{
	int n;
	if ((n = getaddrinfo (host, service, hint, res)) != 0)
		wp_error_warning ("getaddrinfo() error: %s", gai_strerror (n));
	return n;
}

int wp_getnameinfo (const struct sockaddr *addr, socklen_t alen, char *host, socklen_t hostlen, char *service, socklen_t servlen, unsigned int flags)
{
	int n;
	if ((n = getnameinfo (addr, alen, host, hostlen, service, servlen, flags)) != 0)
		wp_error_warning ("getnameinfo() error: %s", gai_strerror (n));
	return n;
}

