#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <pthread.h>
#include "sniff.h"
#include "liststore.h"

// WSAIoctl option
#define SIO_RCVALL				(IOC_IN|IOC_VENDOR|1)

#define HI_WORD(byte)    (((byte) >> 4) & 0x0F)
#define LO_WORD(byte)    ((byte) & 0x0F)

// A list of protocol types in the IP protocol header
char *szProto[] = {"Reserved",     //  0
                   "ICMP",         //  1
                   "IGMP",         //  2
                   "GGP",          //  3
                   "IP",           //  4
                   "ST",           //  5
                   "TCP",          //  6
                   "UCL",          //  7
                   "EGP",          //  8
                   "IGP",          //  9
                   "BBN-RCC-MON",  // 10
                   "NVP-II",       // 11
                   "PUP",          // 12
                   "ARGUS",        // 13
                   "EMCON",        // 14
                   "XNET",         // 15
                   "CHAOS",        // 16
                   "UDP",          // 17
                   "MUX",          // 18
                   "DCN-MEAS",     // 19
                   "HMP",          // 20
                   "PRM",          // 21
                   "XNS-IDP",      // 22
                   "TRUNK-1",      // 23
                   "TRUNK-2",      // 24
                   "LEAF-1",       // 25
                   "LEAF-2",       // 26
                   "RDP",          // 27
                   "IRTP",         // 28
                   "ISO-TP4",      // 29
                   "NETBLT",       // 30
                   "MFE-NSP",      // 31
                   "MERIT-INP",    // 32
                   "SEP",          // 33
                   "3PC",          // 34
                   "IDPR",         // 35
                   "XTP",          // 36
                   "DDP",          // 37
                   "IDPR-CMTP",    // 38
                   "TP++",         // 39
                   "IL",           // 40
                   "SIP",          // 41
                   "SDRP",         // 42
                   "SIP-SR",       // 43
                   "SIP-FRAG",     // 44
                   "IDRP",         // 45
                   "RSVP",         // 46
                   "GRE",          // 47
                   "MHRP",         // 48
                   "BNA",          // 49
                   "SIPP-ESP",     // 50
                   "SIPP-AH",      // 51
                   "I-NLSP",       // 52
                   "SWIPE",        // 53
                   "NHRP",         // 54
                   "unassigned",   // 55
                   "unassigned",   // 56
                   "unassigned",   // 57
                   "unassigned",   // 58
                   "unassigned",   // 59
                   "unassigned",   // 60
                   "any host internal protocol",  // 61
                   "CFTP",         // 62
                   "any local network",           // 63
                   "SAT-EXPAK",    // 64
                   "KRYPTOLAN",    // 65
                   "RVD",          // 66
                   "IPPC",         // 67
                   "any distributed file system", // 68
                   "SAT-MON",    // 69
                   "VISA",       // 70
                   "IPCV",       // 71
                   "CPNX",       // 72
                   "CPHB",       // 73
                   "WSN",        // 74
                   "PVP",        // 75
                   "BR-SAT-MON", // 76
                   "SUN-ND",     // 77
                   "WB-MON",     // 78
                   "WB-EXPAK",   // 79
                   "ISO-IP",     // 80
                   "VMTP",       // 81
                   "SECURE-VMTP",// 82
                   "VINES",      // 83
                   "TTP",        // 84
                   "NSFNET-IGP", // 85
                   "DGP",        // 86
                   "TCF",        // 87
                   "IGRP",       // 88
                   "OSPFIGP",    // 89
                   "Sprite-RPC", // 90
                   "LARP",       // 91
                   "MTP",        // 92
                   "AX.25",      // 93
                   "IPIP",       // 94
                   "MICP",       // 95
                   "SCC-SP",     // 96
                   "ETHERIP",    // 97
                   "ENCAP",      // 98
                   "any private encryption scheme",    // 98
                   "GMTP"        // 99
};

unsigned long dwProtocol=IPPROTO_IP;
unsigned long dwInterface=0;
unsigned long dwIoControlCode=SIO_RCVALL;

#define HI_WORD(byte)    (((byte) >> 4) & 0x0F)
#define LO_WORD(byte)    ((byte) & 0x0F)

#define UDP_HEAD_LEN 8	/* UDP head length */
#define ICMP_HEAD_LEN 4	/* ICMP head length */

#define QUEUE_SIZE 1024

static char buffer[65535];

QueueElementType q, r;

struct TCPPacketHead {
	WORD SourPort;
	WORD DestPort;
	DWORD SeqNo;
	DWORD AckNo;
	BYTE HLen;
	BYTE Flag;
	WORD WndSize;
	WORD ChkSum;
	WORD UrgPtr;
};

static gboolean timeout_callback (Sniff *sniff) {

	while (!IsEmpty (sniff->queue))
	{
		r = Front (sniff->queue);
		liststore_insert (GTK_TREE_VIEW (sniff->treeview), r.protocol, r.sip, r.sport, r.dip, r.dport, r.size, r.pdata);
		Dequeue (sniff->queue);
	}
//	printf ("timeout_callback\n");
	return TRUE;
}

// Decode TCP/IP header.
static int decode(char *hdr, Queue queue)
{
	SOCKADDR_IN stSrc,stDest;
	unsigned short ip_version,
                   ip_hdr_len,
                   ip_tos,
                   ip_total_len,
                   ip_id,
                   ip_flags,
                   ip_ttl,
                   ip_frag_offset,
                   ip_proto,
                   ip_hdr_chksum,
                   ip_src_port,
                   ip_dest_port;
	unsigned int   ip_src,ip_dest;
	unsigned short usVal;
	char *tcpip;

	char *sip;
	char *dip;

	ip_version = (unsigned short)HI_WORD(*hdr);
	ip_hdr_len = (unsigned short)(LO_WORD(*hdr) * 4);
	tcpip= (char *)(hdr + ip_hdr_len);
	hdr++;

	ip_tos = *hdr;
	hdr++;

	memcpy(&usVal, hdr, 2);
	ip_total_len = ntohs(usVal);
	hdr += 2;

	memcpy(&usVal, hdr, 2);
	ip_id = ntohs(usVal);
	hdr += 2;

	ip_flags = (unsigned short)((*hdr) >> 5);

	memcpy(&usVal, hdr, 2);
	ip_frag_offset = (unsigned short)((ntohs(usVal)) & 0x1FFF);
	hdr+=2;

	ip_ttl = *hdr;
	hdr++;

	ip_proto = *hdr;
	hdr++;

	memcpy(&usVal, hdr, 2);
	ip_hdr_chksum = ntohs(usVal);
	hdr += 2;

	memcpy(&stSrc.sin_addr.s_addr, hdr, 4);
	ip_src = ntohl(stSrc.sin_addr.s_addr);
	hdr += 4;

	memcpy(&stDest.sin_addr.s_addr, hdr, 4);
	ip_dest = ntohl(stDest.sin_addr.s_addr);
	hdr += 4;


	switch(ip_proto){
		case 1: // ICMP
		case 6: // TCP
		case 17: //UDP
			memcpy(&ip_src_port,tcpip,2);
			ip_src_port=ntohs(ip_src_port);
			memcpy(&ip_dest_port,tcpip+2,2);
			ip_dest_port=ntohs(ip_dest_port);
			sip = inet_ntoa (stSrc.sin_addr);
			dip = inet_ntoa (stDest.sin_addr);
			break;
		default:
			ip_src_port = 0;
			ip_dest_port = 0;
			sip = NULL;
			dip = NULL;
			break;
	}

	unsigned short data_size = 0;
	unsigned short tcp_len = 0;
	switch(ip_proto) {
		case 1:
			hdr += ICMP_HEAD_LEN;
			data_size = ip_total_len - ip_hdr_len - ICMP_HEAD_LEN;
			break;
		case 6:
			hdr += 12;
			tcp_len = (unsigned short)HI_WORD(*hdr);
			tcp_len *= 4;
			data_size = ip_total_len - ip_hdr_len - tcp_len;
			hdr += 8;
			break;
		case 17:
			hdr += UDP_HEAD_LEN;
			data_size = ip_total_len - ip_hdr_len - UDP_HEAD_LEN;
			break;
		default:
			data_size = ip_total_len - ip_hdr_len;
			break;
	}

//	printf ("DEBUG: header length %d\t total length: %d\n", ip_hdr_len, ip_total_len);
//	printf ("DEBUG: data size: %d\n", data_size);

	buffer[0] = '\0';
	memcpy (buffer, hdr, data_size);
	buffer[data_size] = '\0';
//	printf ("DEBUG: DATA: %s\n", buffer);
//	printf ("protocol: %s sip: %s sport: %d dip: %s dport: %d size: %d data: %s\n", szProto[ip_proto], sip, ip_src_port, dip, ip_dest_port, data_size, buffer);

//	
	q.protocol = szProto[ip_proto];
	q.sip = sip;
	q.sport = ip_src_port;
	q.dip = dip;
	q.dport = ip_dest_port;
	q.size = data_size;
	q.pdata = buffer;

	Enqueue (q, queue);

	return 0;
}

// Get all local IP interfaces.
static int getif(SOCKET s,SOCKADDR_IN *if0,unsigned long dwNum)
{
	SOCKET_ADDRESS_LIST *pstList=NULL;
	unsigned long dwBytesRet;
	char szBuf[4096];
	int  nRet;
	
	nRet=WSAIoctl(s, SIO_ADDRESS_LIST_QUERY, NULL,0,szBuf, 4096, &dwBytesRet, NULL,NULL);
	if(nRet==SOCKET_ERROR){
		printf("WSAIoctl(SIO_ADDRESS_LIST_QUERY) failed!Error code:%d\n",WSAGetLastError());
		return 1;
	}

	pstList=(SOCKET_ADDRESS_LIST *)szBuf;
	if((int)(dwNum)>=pstList->iAddressCount){
		return 1;
	}
	if0->sin_addr.s_addr=((SOCKADDR_IN *)pstList->Address[dwNum].lpSockaddr)->sin_addr.s_addr;

	return 0;
}

static void* thread_func(gpointer data)
{
	Sniff *sniff = (Sniff *) data;

	WSADATA  stWsaData;
	SOCKET     s;
	SOCKADDR_IN if0;
	unsigned int  uiOptval;
	unsigned long dwBytesRet;
	int nRet;
	char szBuff[65535];

	if(WSAStartup(MAKEWORD(2, 2),&stWsaData)!=0)
	{
		printf("WSAStartup() failed!Error code:%d\n",WSAGetLastError());
		return NULL;
	}

	s=socket(AF_INET,SOCK_RAW,dwProtocol);
	if(s==INVALID_SOCKET){
		printf("socket() failed!Error code:%d\n",WSAGetLastError());
		return NULL;
	}
	// Get an interface to read IP packets on
	if(getif(s,&if0,dwInterface)!=0)
	{
		printf("Unable to obtain an interface!\n");
		return NULL;
	}
	printf("Binding to if:%s\n",inet_ntoa(if0.sin_addr));
	
	// This socket must be bound before calling the ioctl
	if0.sin_family=AF_INET;
	if0.sin_port=htons(0);

	if(bind(s,(SOCKADDR *)&if0,sizeof(if0))==SOCKET_ERROR){
		printf("bind() falied!Error code:%d\n",WSAGetLastError());
		return NULL;
	}
		
	uiOptval=1;
	if(WSAIoctl(s,dwIoControlCode,&uiOptval,sizeof(uiOptval),NULL,0,&dwBytesRet,NULL,NULL)==SOCKET_ERROR)
	{
		printf("WSAIoctl(%ld) failed,Error code:%d\n",dwIoControlCode,WSAGetLastError());

		return NULL;
	}

	gint timer;
	timer = g_timeout_add (100, (GSourceFunc)timeout_callback, sniff);
	while(sniff->status){
		nRet=recv(s,szBuff,sizeof(szBuff),0);
		if(nRet==SOCKET_ERROR)
		{
			printf("recv() failed!Error code:%d\n",WSAGetLastError());
			return NULL;
		}
		decode(szBuff, sniff->queue);
	}

	g_source_remove (timer);

	closesocket(s);
	WSACleanup();

	while (!IsEmpty (sniff->queue)) {
		timeout_callback(sniff);
	}

	return NULL;
}

void on_check_clicked (GtkButton *check, gpointer data) {
	Sniff *sniff = (Sniff *) data;
	if (sniff->status == 0) {
		gtk_button_set_label (GTK_BUTTON (sniff->button), "停止查看");

		sniff->status = 1;
		if (pthread_create (&(sniff->thread), NULL, thread_func, data)) {
			fprintf (stderr, "Error creating thread\n");
			exit (2);
		}
	} else if ( sniff->status == 1 ) {
		sniff->status = 0;

		if (pthread_join (sniff->thread, NULL)) {
			fprintf (stderr, "Error joining thread\n");
			exit (1);
		}

		gtk_button_set_label (GTK_BUTTON (sniff->button), "查看");
	}
}
