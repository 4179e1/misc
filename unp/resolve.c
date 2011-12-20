#if 0
clang -Wall -g -o `basename $0 .c` $0 `pkg-config --cflags --libs glib-2.0`
exit 0
#endif

#include <glib.h>
#include <arpa/inet.h>
#include <netdb.h>

char *resolve_hostip (const char *hostname)
{
	char **pp;
	struct in_addr addr;
	struct hostent *hostp;
	char ip[INET_ADDRSTRLEN];

	if (g_hostname_is_ip_address (hostname))
	{
		return g_strdup (hostname);
	}
	
	hostp = gethostbyname (hostname);
	if (hostp == NULL)
	{
		return NULL;
	}

	pp = hostp->h_addr_list; 
	addr.s_addr = *((unsigned int *)*pp);
	inet_ntop (AF_INET, &addr, ip, sizeof (ip));
	
	return g_strdup (ip);
}

int main (int argc, char *argv[])
{
	if (argc < 2)
	{
		g_critical ("usage: %s <hostname>", argv[0]);
	}

	g_message ("%s", resolve_hostip (argv[1]));

	
	return 0;
}
