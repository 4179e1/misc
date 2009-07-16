#ifndef _ICMP_H
#define _ICMP_H
#include <gtk/gtk.h>
#include <pthread.h>

typedef struct {
	GtkWidget *treeview;
	GtkWidget *entry;
	GtkWidget *ping;
	GtkWidget *trace;
	GtkWidget *stop;
	pthread_t thread;
	char hostname[1024];
	int status;
	int size;
	int time;
	int num;
} Icmp;

#define DEFAULT_HOSTNAME "lyre-9a2dcc57f0."
#define DEFAULT_BUFF	"32"
#define DEFAULT_TIME	"1000"
#define DEFAULT_NUM		"3"

#endif
