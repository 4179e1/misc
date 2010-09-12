#if 0
gcc -c -Wall -o `basename $0 .c` $0
exit 0
#endif

#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#ifndef LISTENQ
#define LISTENQ 1024
#endif /* LISTENQ */

int open_clientfd (char *hostname, int port)
{
	int clientfd;
	struct hostent *hp;
	struct sockaddr_in servaddr;

	if ((clientfd = socket (AF_INET, SOCK_STREAM, 0) < 0))
	{
		return -1;
	}

	if ((hp = gethostbyname (hostname)) == NULL)
	{
		return -2;
	}

	memset (&servaddr, 0, sizeof (servaddr));
	servaddr.sin_family = AF_INET;
	memcpy (&(servaddr.sin_addr.s_addr), hp->h_addr, hp->h_length);
	servaddr.sin_port = htons(port);

	if (connect (clientfd, (struct sockaddr*)&servaddr, sizeof (servaddr)) < 0)
	{
		return -1;
	}

	return clientfd;
}

int open_listenfd (int port)
{
	int listenfd, optval = 1;
	struct sockaddr_in servaddr;

	if ((listenfd = socket (AF_INET, SOCK_STREAM, 0)) < 0)
	{
		return -1;
	}

	if (setsockopt (listenfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof (int)) < 0)
	{
		return -1;
	}

	memset (&servaddr, 0, sizeof (servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons ((unsigned short)port);

	if (bind (listenfd, (struct sockaddr*)&servaddr, sizeof (servaddr)) < 0)
	{
		return -1;
	}

	if (listen (listenfd, LISTENQ) < 0)
	{
		return -1;
	}

	return listenfd;
}
