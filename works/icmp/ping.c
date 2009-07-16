#include <gtk/gtk.h>
#include <pthread.h>
#include <winsock2.h>
#include <time.h>
#include "icmp.h"
#include "ping.h"
#include "socket.h"
#include "handler.h"
#include "liststore.h"
#include "queue.h"

static QueueElementType q, r;
static Queue queue;

static gboolean timeout_callback (Icmp *icmp) {
	while (!IsEmpty (queue)) {
		r = FrontAndDequeue (queue);
		liststore_insert (GTK_TREE_VIEW (icmp->treeview), r.num, r.time, r.ip, r.msg);
	}
	return TRUE;
}

static void *ping_func (gpointer data) {
	Icmp *icmp = (Icmp *) data;

	clock_t start, finish;
	struct in_addr addr;

	queue = CreateQueue (icmp->num);

	gint timer;

	socket_init();

	start = clock();

	struct hostent *host = gethostbyname (icmp->hostname);

	finish = clock();


	if (host == NULL) {
//		error_message ("ERROR: no such host\n");
		liststore_insert (GTK_TREE_VIEW (icmp->treeview), 0, (int)(finish-start), "-", "ping - unkown host");
		return ((void *) 1);
	}

	addr.s_addr = *(u_long *)host->h_addr_list[0];

//	printf ("%s\n", inet_ntoa (addr));

	SOCKET			hSocket			=INVALID_SOCKET;
	SOCKADDR_IN		dstSin;
	SOCKADDR_IN		fromSin;
	char*			pIcmpData		=NULL;
	char*			pRecvData		=NULL;
	char*			lpDstIp			=inet_ntoa (addr);
	int				datasize		= icmp->size;
	int				ret;
	

	

	//创建AFINET地址族的SOCK_RAW类型的套接字
	//
	hSocket=WSASocket(AF_INET,SOCK_RAW,IPPROTO_ICMP,NULL,0,WSA_FLAG_OVERLAPPED);
	if(hSocket==INVALID_SOCKET)//创建失败返回ERROR
	{
		printf("WSASocket Error,Code:%d",WSAGetLastError());
		WSACleanup();
		gtk_widget_set_sensitive (icmp->ping, TRUE);
		gtk_widget_set_sensitive (icmp->trace, TRUE);
		return NULL;
	}

	timer = g_timeout_add (100, (GSourceFunc)timeout_callback, icmp);
	//set socket recv and send timeout;
	int timeout=icmp->time;
	if((ret=setsockopt(hSocket,SOL_SOCKET,SO_RCVTIMEO,(char *)&timeout,sizeof(timeout)))==SOCKET_ERROR)
	{
		printf("setsockopt(SO_RCVTIMEO) error,code:%d",WSAGetLastError());
		WSACleanup();
		closesocket(hSocket);
		gtk_widget_set_sensitive (icmp->ping, TRUE);
		gtk_widget_set_sensitive (icmp->trace, TRUE);
		return NULL;
	}
	if((ret=setsockopt(hSocket,SOL_SOCKET,SO_SNDTIMEO,(char *)&timeout,sizeof(timeout)))==SOCKET_ERROR){
		printf("setsockopt(SO_SNDTIMEO) error,code:%d",WSAGetLastError());
		WSACleanup();
		gtk_widget_set_sensitive (icmp->ping, TRUE);
		gtk_widget_set_sensitive (icmp->trace, TRUE);
		return NULL;
	}
	
	pIcmpData=(char *)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,MAX_PACKET_SIZE);
	pRecvData=(char *)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,MAX_PACKET_SIZE);
	if(pIcmpData==NULL||pRecvData==NULL)
	{
		printf("HeapAlloc Error\n");
		WSACleanup();
		gtk_widget_set_sensitive (icmp->ping, TRUE);
		gtk_widget_set_sensitive (icmp->trace, TRUE);
		return NULL;
	}
	datasize+=sizeof(ICMP_HEADER);
	ZeroMemory(&dstSin,sizeof(dstSin));
	dstSin.sin_family=AF_INET;
	dstSin.sin_addr.s_addr=inet_addr(lpDstIp);
	FillIcmpData(pIcmpData,datasize);
//	printf("Ping %s with %d bytes of data\n",inet_ntoa(dstSin.sin_addr),datasize);
	int count=0;
	int seq=0;
	int rcvNum=0;


	icmp->status = 1;

	while(count < icmp->num)
	{
		if (icmp->status == 0)
			break;

		count++;

		((PICMP_HEADER)pIcmpData)->checksum=0;
		((PICMP_HEADER)pIcmpData)->seq=seq++;
		((PICMP_HEADER)pIcmpData)->timestamp=GetTickCount();
		((PICMP_HEADER)pIcmpData)->checksum=
			CheckSum((USHORT*)pIcmpData,datasize);
		start = clock();
		if((ret=sendto(hSocket,pIcmpData,datasize,0,(LPSOCKADDR)&dstSin,sizeof(dstSin)))==SOCKET_ERROR){
			finish = clock();
			if(WSAGetLastError()==WSAETIMEDOUT){
//				printf("time out.\n");
				liststore_insert (GTK_TREE_VIEW (icmp->treeview), seq, (int) (finish - start), inet_ntoa (addr), "ping - sending time out");
				continue;
			}
			else{
				printf("sendto error,code:%d",WSAGetLastError());
				closesocket(hSocket);
				WSACleanup();
				gtk_widget_set_sensitive (icmp->ping, TRUE);
				gtk_widget_set_sensitive (icmp->trace, TRUE);
				return NULL;
			}
		}
		int fromLen=sizeof(fromSin);
		start = clock();
		if((ret=recvfrom(hSocket,pRecvData,MAX_PACKET_SIZE,0,(struct sockaddr *)&fromSin,
			&fromLen))==SOCKET_ERROR){
			finish = clock ();
			if(WSAGetLastError()==WSAETIMEDOUT)
			{
//				printf("time out.\n");
				liststore_insert (GTK_TREE_VIEW (icmp->treeview), rcvNum, (int) (finish - start), inet_ntoa (addr), "pint - receving time out");
				continue;
			}
			printf("recvform fail!\n");
			closesocket(hSocket);
			WSACleanup();
			gtk_widget_set_sensitive (icmp->ping, TRUE);
			gtk_widget_set_sensitive (icmp->trace, TRUE);
			return NULL;
		}
		rcvNum++;
		DecodeIcmpHeader(pRecvData,ret,&fromSin,data);
	}
	
//	printf("\n Ping Statistics for : %s\n",lpDstIp);
//	printf("\t Send= %d, Received= %d,Lost= %d (%d%% loss)\n",4,rcvNum,4-rcvNum,(4-rcvNum)/4*100);
	
	if(hSocket!=INVALID_SOCKET)
		closesocket(hSocket);

	HeapFree(GetProcessHeap(),0,pIcmpData);
	HeapFree(GetProcessHeap(),0,pRecvData);
/***************/	

	socket_terminal();

	g_source_remove (timer);

	
	if (!IsEmpty (queue)) {
		timeout_callback(icmp);
	}

	gtk_widget_set_sensitive (icmp->ping, TRUE);
	gtk_widget_set_sensitive (icmp->trace, TRUE);
	
	icmp->status = 0;

	DisposeQueue (queue);

	return ((void *) 0);
}

void on_ping_clicked (GtkButton *button, gpointer data) {
	
	Icmp *icmp = (Icmp *) data;

	gtk_widget_set_sensitive (icmp->ping, FALSE);
	gtk_widget_set_sensitive (icmp->trace, FALSE);

	const char *hostname = gtk_entry_get_text (GTK_ENTRY (icmp->entry));

	if (strcmp (hostname, "") == 0) {
		error_message ("Empty host");
		return;
	} else
		strcpy (icmp->hostname, hostname);

	if (pthread_create (&(icmp->thread), NULL, ping_func, data)) {
		fprintf (stderr, "Error creating thread\n");
		exit (2);
	}
}


void FillIcmpData(char *icmp_data,int size)
{
	ICMP_HEADER *icmpHdr;
	icmpHdr=(PICMP_HEADER)icmp_data;
	icmpHdr->checksum=0;
	icmpHdr->code=0;
	icmpHdr->id=(unsigned short)GetCurrentProcessId();
	icmpHdr->seq=0;
	icmpHdr->type=ICMP_ECHO;
	icmpHdr->timestamp=0;
}

USHORT CheckSum(USHORT *buf,int size)
{			//check sum function
	USHORT cksum=0;
	while(size>1)
	{
		cksum+=*buf++;
		size-=sizeof(USHORT);
	}
	if(size)
		cksum+=*buf++;
	cksum=(cksum>>16)+(cksum&0xffff);
	cksum+=(cksum>>16);
	return (USHORT)(~cksum);
}

void DecodeIcmpHeader(char *buf,int ret,LPSOCKADDR_IN lpSin, gpointer data)
{
	Icmp *icmp = (Icmp *)data;

	ICMP_HEADER *icmpHdr;
	IP_HEADER	*ipHdr;
	int ipHdrLen;
	static int first=0;
	DWORD tick=GetTickCount();
	ipHdr=(IP_HEADER*)buf;
	ipHdrLen=ipHdr->h_len*4;

	icmpHdr=(ICMP_HEADER *)(buf+ipHdrLen);
	if(icmpHdr->type!=ICMP_ECHOREPLY){
//		printf("no echo reply %d recved\n",icmpHdr->type);
		liststore_insert (GTK_TREE_VIEW (icmp->treeview), icmpHdr->seq, tick-icmpHdr->timestamp, inet_ntoa(lpSin->sin_addr), "ping - no echo reply recved");
		return;
	}
	if(icmpHdr->id!=(USHORT)GetCurrentProcessId()){
//		printf("someone else's packet!\n");
		liststore_insert (GTK_TREE_VIEW (icmp->treeview), icmpHdr->seq, tick-icmpHdr->timestamp, inet_ntoa(lpSin->sin_addr), "ping - someone else's packet");
		return;
	}

	q.num = icmpHdr->seq;
	q.time = tick-icmpHdr->timestamp;
	q.ip = inet_ntoa (lpSin->sin_addr);
	q.msg = "ping - ok";

	Enqueue (q, queue);
	first++;
	
	return;
}
