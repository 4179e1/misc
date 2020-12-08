#ifndef _PING_H
#define _PING_H
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <gtk/gtk.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct tagIP_HEADER{
	unsigned int	h_len:4;				//length of header	(4b)
	unsigned int	ver:4;					//version			(4b)
	unsigned char	tos;					//tos				(1B)
	unsigned short	total_len;				//total length		(2B)
	unsigned short	ident;					//identification	(2B)
	unsigned short	frag_flags;				//frag and flags	(2B)
	unsigned char	ttl;					//time of lives		(1B)
	unsigned char	protocol;				//protocol			(1B)
	unsigned short	checksum;				//checksum			(2B)
	unsigned int	sourceip;				//source ip			(4B)
	unsigned int	destip;					//destination ip	(4B)
}IP_HEADER,*PIP_HEADER;						//length of total	(20B)

/*
typedef struct tagIP_OPT_HEADER{
	unsigned char code;			//option type					(1B)
	unsigned char len;			//length of option header		(1B)
	unsigned char ptr;			//下一个可存放地址的位置		(1B)
	unsigned long addr[9];		//list of ip address			(4B/d)
}IP_OPT_HEADER,*PIP_OPT_HEADER;	//length of total				(39B)
*/
//定义ICMP头
typedef struct tagICMP_HEADER{
	unsigned char	type;					//icmp type			(1B)
	unsigned char	code;					//code of type		(1B)
	unsigned short	checksum;				//checksum			(2B)
	unsigned short	id;						//identification	(2B)
	unsigned short	seq;					//sequence			(2B)
	unsigned long	timestamp;				//					(2B)
					//this is not standard header,but we reserve space for time
}ICMP_HEADER,*PICMP_HEADER;					//total length		(10B)

#define		DEF_PACKET_SIZE		32
#define		MAX_PACKET_SIZE		1024
#define		ICMP_ECHO			8
#define		ICMP_ECHOREPLY		0
#define		IP_RECORD_ROUTER	7

void FillIcmpData(char *icmp_data,int size);
USHORT CheckSum(USHORT *buf,int size);
void DecodeIcmpHeader(char *buf,int ret,LPSOCKADDR_IN lpSin, gpointer data);
//void DecodeIpHeader(char *buf,int bytes);
void on_ping_clicked (GtkButton *button, gpointer data);

#endif
