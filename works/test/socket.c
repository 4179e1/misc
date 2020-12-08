#include <stdio.h>
#include <winsock2.h>
#include <iphlpapi.h>
#include <stdlib.h>

#define MINORVER 2
#define MAJORVER 2

void socket_init (void) {
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(MINORVER,MAJORVER);
	if (WSAStartup(sockVersion, &wsaData) != 0 )
	{
		fprintf (stderr, "ERROR\n");
		exit(1);
	}
}

void socket_terminal (void) {
	WSACleanup();
}

int main (int argc, char *argv[]) {
	socket_init();

	struct hostent *host = gethostbyname ("lyre-9a2dcc57f0.");

	struct in_addr addr;

	if (host == NULL) {
		fprintf (stderr, "ERROR: not sach host\n");
		exit (1);
	}

	addr.s_addr = *(u_long *)host->h_addr_list[0];

	printf ("%s\n", inet_ntoa (addr));
	socket_terminal();

	return 0;
}
