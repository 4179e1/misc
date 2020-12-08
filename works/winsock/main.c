#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <iphlpapi.h>
#include <windows.h>

#define MINORVER 2
#define MAJORVER 2

int main (int argc, char *argv[])
{
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(MINORVER,MAJORVER);
	if (WSAStartup(sockVersion, &wsaData) != 0 )
	{
		fprintf (stderr, "ERROR\n");
		exit(1);
	}

	char *strHost = 0;
//	gethostname(strHost,256);
	struct hostent *pHost = gethostbyname (strHost);
	printf ("Host name: %s\n", pHost->h_name);

	struct in_addr addr;
	char *p;
	char *strIP;
	int i;
	for (i = 0; ; i++) {
		p = pHost->h_addr_list[i];

		if (p == NULL)
			break;

		memcpy (&addr.S_un.S_addr, p, pHost->h_length);
		strIP = inet_ntoa (addr);
		printf ("Local IP Address: %s\n", strIP);
	}

	char LocalMac[6];
	long GatewayIP;
	long LocalIP;
	long Mask;

	IP_ADAPTER_INFO *AdapterInfo = NULL;
	long Len = 0;

	GetAdaptersInfo (AdapterInfo, &Len);
	AdapterInfo = (PIP_ADAPTER_INFO) GlobalAlloc (GPTR, Len);

	if (GetAdaptersInfo (AdapterInfo, &Len) == ERROR_SUCCESS) {
		while (AdapterInfo != NULL) {
			memcpy (LocalMac, AdapterInfo->Address, 6);
			GatewayIP = inet_addr (AdapterInfo->GatewayList.IpAddress.String);
			LocalIP = inet_addr (AdapterInfo->IpAddressList.IpMask.String);
			Mask = inet_addr (AdapterInfo->IpAddressList.IpMask.String);

			printf ("==========Local Host Information==========\n");
			printf ("Adapter Name: %s\n", AdapterInfo->AdapterName);
			printf ("Adapter Description: %s\n", AdapterInfo->Description);
			
			struct in_addr in;
			
			in.S_un.S_addr = LocalIP;
			printf ("IP Address: %s \n", inet_ntoa (in));
			in.S_un.S_addr = Mask;
			printf ("Subnet Mask: %s \n", inet_ntoa (in));
			in.S_un.S_addr = GatewayIP;
			printf ("Default Gateway: %s \n", inet_ntoa (in));

			p = LocalMac;
			printf("MAC Address: %02X-%02X-%02X-%02X-%02X-%02X\n",p[0],p[1],p[2],p[3],p[4],p[5]);
			AdapterInfo = AdapterInfo->Next;
		}
	}

	WSACleanup();
	return 0;
}
