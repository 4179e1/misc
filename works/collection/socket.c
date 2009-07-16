#include <stdio.h>
#include <winsock2.h>
#include <stdlib.h>
#include "socket.h"

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
