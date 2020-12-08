#include <gtk/gtk.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include <IPHlpApi.h>
#include <stdlib.h>
#include <time.h>
#include "icmp.h"
#include "trace.h"
#include "queue.h"
#include "handler.h"
#include "socket.h"
#include "liststore.h"


//声明3个函数类型的指针
typedef HANDLE (WINAPI *lpIcmpCreateFile)(VOID);
typedef BOOL (WINAPI *lpIcmpCloseHandle)(HANDLE  IcmpHandle);
typedef DWORD (WINAPI *lpIcmpSendEcho)(
									   HANDLE                   IcmpHandle,
									   IPAddr                   DestinationAddress,
									   LPVOID                   RequestData,
									   WORD                     RequestSize,
									   PIP_OPTION_INFORMATION   RequestOptions,
									   LPVOID                   ReplyBuffer,
									   DWORD                    ReplySize,
									   DWORD                    Timeout
									   );

static QueueElementType q, r;
static Queue queue;

static gboolean timeout_callback (Icmp *icmp) {
	while (!IsEmpty (queue)) {
		r = FrontAndDequeue (queue);
		liststore_insert (GTK_TREE_VIEW (icmp->treeview), r.num, r.time, r.ip, r.msg);
	}
	return TRUE;
}

static void *trace_func (gpointer data) {
	Icmp *icmp = (Icmp *) data;

	clock_t start, finish;

	gint timer;

	queue = CreateQueue (icmp->size);

/*********************/

	socket_init();

	start = clock();
	struct hostent* pHost = gethostbyname(icmp->hostname);
	finish = clock ();
	//如果域名无法解析
	if(pHost==NULL){
//		printf("Invalid IP or domain name: %s\n", icmp->hostname);
		liststore_insert (GTK_TREE_VIEW (icmp->treeview), 0, (int)finish - start, "-", "trace - unkown host");
		gtk_widget_set_sensitive (icmp->ping, TRUE);
		gtk_widget_set_sensitive (icmp->trace, TRUE);
		return NULL;
	}
	//取域名的第一个IP地址
	unsigned long ip = *(unsigned long*)pHost->h_addr_list[0];
//	printf("trace route to %s(%s)\n\n",icmp->hostname,inet_ntoa(*(struct in_addr*)&ip));

	//载入ICMP.DLL动态库
	HMODULE hIcmpDll = LoadLibrary(("icmp.dll"));
	if(hIcmpDll==NULL){
		printf("fail to load icmp.dll\n");
		gtk_widget_set_sensitive (icmp->ping, TRUE);
		gtk_widget_set_sensitive (icmp->trace, TRUE);
		return NULL;
	}
	//定义3个函数指针
	lpIcmpCreateFile IcmpCreateFile;
	lpIcmpCloseHandle IcmpCloseHandle;
	lpIcmpSendEcho IcmpSendEcho;

	//从ICMP.DLL中获取所需的函数入口地址
	IcmpCreateFile = (lpIcmpCreateFile)GetProcAddress(hIcmpDll,"IcmpCreateFile");
	IcmpCloseHandle = (lpIcmpCloseHandle)GetProcAddress(hIcmpDll,"IcmpCloseHandle");
	IcmpSendEcho = (lpIcmpSendEcho)GetProcAddress(hIcmpDll,"IcmpSendEcho");

	//打开ICMP句柄
	HANDLE hIcmp;
	if ((hIcmp = IcmpCreateFile()) == INVALID_HANDLE_VALUE){
		printf("\tUnable to open ICMP file.\n");
		gtk_widget_set_sensitive (icmp->ping, TRUE);
		gtk_widget_set_sensitive (icmp->trace, TRUE);
		return NULL;
	}

	//设置IP报头的TTL值
	IP_OPTION_INFORMATION IpOption;
	ZeroMemory(&IpOption,sizeof(IP_OPTION_INFORMATION));
	IpOption.Ttl = 1;

	//设置要发送的数据
	char SendData[icmp->size];
	memset(SendData,'0',sizeof(SendData));

	//设置接收缓冲区
	char ReplyBuffer[sizeof(ICMP_ECHO_REPLY)+icmp->size];
	PICMP_ECHO_REPLY pEchoReply = (PICMP_ECHO_REPLY)ReplyBuffer;

	BOOL bLoop = TRUE;
	int iMaxHop = icmp->num;

	timer = g_timeout_add (100, (GSourceFunc)timeout_callback, icmp);

	icmp->status = 1;
	while(bLoop && iMaxHop--){

		if (icmp->status == 0)
			break;

		//发送ICMP回显请求
		start = clock();
		if(IcmpSendEcho(hIcmp,(IPAddr)ip, SendData, sizeof(SendData), &IpOption, 
			ReplyBuffer, sizeof(ReplyBuffer), icmp->time)!=0){
			finish = clock();
		
				q.num = IpOption.Ttl;
				q.time = pEchoReply->RoundTripTime;
				q.ip = inet_ntoa(*(struct in_addr*)&(pEchoReply->Address));
				q.msg = "trace - ok";

				Enqueue (q, queue);
				//判断是否完成路由路径探测
				if((unsigned long)pEchoReply->Address==ip){
//					printf("\nTrace complete.\n");
					bLoop = FALSE;
				}
		}else{
				q.num = IpOption.Ttl;
				q.time = (int)finish - start;
				q.ip = "*";
				q.msg = "trace - Request time out";
				Enqueue (q, queue);
			
		}
		IpOption.Ttl++;
	}
	g_source_remove (timer);
	icmp->status = 0;

	IcmpCloseHandle(hIcmp);

	FreeLibrary(hIcmpDll);

	WSACleanup();
/*********************/
	
	if (!IsEmpty (queue))
	{
		timeout_callback (icmp);
	}

	DisposeQueue (queue);

	gtk_widget_set_sensitive (icmp->ping, TRUE);
	gtk_widget_set_sensitive (icmp->trace, TRUE);

	return ((void *) 0);
}

void on_trace_clicked (GtkButton *button, gpointer data) {
	
	Icmp *icmp = (Icmp *) data;

	gtk_widget_set_sensitive (icmp->ping, FALSE);
	gtk_widget_set_sensitive (icmp->trace, FALSE);

	const char *hostname = gtk_entry_get_text (GTK_ENTRY (icmp->entry));

	if (strcmp (hostname, "") == 0) {
		error_message ("Empty host");
		return;
	} else
		strcpy (icmp->hostname, hostname);

	if (pthread_create (&(icmp->thread), NULL, trace_func, data)) {
		fprintf (stderr, "Error creating thread\n");
		exit (2);
	}
}
