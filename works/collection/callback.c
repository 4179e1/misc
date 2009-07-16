#include <gtk/gtk.h>
#include <stdlib.h>
#include <winsock2.h>
#include <iphlpapi.h>
#include <windows.h>
#include "collection.h"
#include "socket.h"
#include "callback.h"
#include "scan.h"

static GtkTextIter iter;
static GtkTextBuffer *buffer;

static char text[512];

static void clear_text (GtkTextBuffer *buf)
{
	GtkTextIter start;
	GtkTextIter end;

	gtk_text_buffer_get_start_iter (buf, &start);
	gtk_text_buffer_get_end_iter (buf, &end);

	gtk_text_buffer_delete (buf, &start, &end);
}

void acquire_ip (Collection *collection) {
	socket_init();

	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (collection->textview));
	clear_text (buffer);
	gtk_text_buffer_get_iter_at_offset (buffer, &iter, 0);

	char *strHost = 0;
//	gethostname(strHost,256);
	struct hostent *pHost = gethostbyname (strHost);
	sprintf (text, "计算机名: %s\n", pHost->h_name);
	gtk_text_buffer_insert (buffer, &iter, text, -1);

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
		sprintf (text, "主机IP地址: %s\n", strIP);
		gtk_text_buffer_insert (buffer, &iter, text, -1);
	}

	long Mask;

	IP_ADAPTER_INFO *AdapterInfo = NULL;
	long Len = 0;

	GetAdaptersInfo (AdapterInfo, &Len);
	AdapterInfo = (PIP_ADAPTER_INFO) GlobalAlloc (GPTR, Len);

	if (GetAdaptersInfo (AdapterInfo, &Len) == ERROR_SUCCESS) {
		while (AdapterInfo != NULL) {
			Mask = inet_addr (AdapterInfo->IpAddressList.IpMask.String);

			struct in_addr in;
			
			in.S_un.S_addr = Mask;
			sprintf (text, "子网掩码: %s \n", inet_ntoa (in));
			gtk_text_buffer_insert (buffer, &iter, text, -1);

			AdapterInfo = AdapterInfo->Next;
		}
	}

	socket_terminal();
}

void acquire_dns (Collection *collection) {
	socket_init();

	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (collection->textview));
	clear_text (buffer);
	gtk_text_buffer_get_iter_at_offset (buffer, &iter, 0);

	long Mask;

	IP_ADAPTER_INFO *AdapterInfo = NULL;
	long Len = 0;

	GetAdaptersInfo (AdapterInfo, &Len);
	AdapterInfo = (PIP_ADAPTER_INFO) GlobalAlloc (GPTR, Len);

	if (GetAdaptersInfo (AdapterInfo, &Len) == ERROR_SUCCESS) {
		while (AdapterInfo != NULL) {
			Mask = inet_addr (AdapterInfo->IpAddressList.IpMask.String);

			struct in_addr in;
			
			in.S_un.S_addr = Mask;
			sprintf (text, "子网掩码: %s \n", inet_ntoa (in));
			gtk_text_buffer_insert (buffer, &iter, text, -1);

			AdapterInfo = AdapterInfo->Next;
		}
	}

	socket_terminal();
}

void acquire_adapter (Collection *collection) {
	socket_init();

	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (collection->textview));
	clear_text (buffer);
	gtk_text_buffer_get_iter_at_offset (buffer, &iter, 0);

	char LocalMac[6];
	char *p;

	IP_ADAPTER_INFO *AdapterInfo = NULL;
	long Len = 0;

	GetAdaptersInfo (AdapterInfo, &Len);
	AdapterInfo = (PIP_ADAPTER_INFO) GlobalAlloc (GPTR, Len);

	if (GetAdaptersInfo (AdapterInfo, &Len) == ERROR_SUCCESS) {
		while (AdapterInfo != NULL) {
			memcpy (LocalMac, AdapterInfo->Address, 6);

			sprintf (text, "网卡类型: %s\n", AdapterInfo->AdapterName);
			gtk_text_buffer_insert (buffer, &iter, text, -1);
			

			gtk_text_buffer_insert (buffer, &iter, "描述:", -1);
			
			char *buf = AdapterInfo->Description;
			char *description = g_convert (buf, -1, "UTF-8", "GBK", NULL, NULL, NULL);
			gtk_text_buffer_insert (buffer, &iter, description, -1);
			gtk_text_buffer_insert (buffer, &iter, "\n", -1);

			p = LocalMac;
			sprintf(text, "网卡MAC地址: %02X-%02X-%02X-%02X-%02X-%02X\n",p[0],p[1],p[2],p[3],p[4],p[5]);
			gtk_text_buffer_insert (buffer, &iter, text, -1);

			AdapterInfo = AdapterInfo->Next;
		}
	}

	socket_terminal();
}

void to_scan (Collection *collection) {
	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (collection->textview));
	clear_text (buffer);
	gtk_text_buffer_get_iter_at_offset (buffer, &iter, 0);

	gtk_text_buffer_insert (buffer, &iter, "端口扫描", -1);
	
	scan (collection);
}

