#ifndef _SNIFF_H
#define _SNIFF_H
#include <pthread.h>
#include "queue.h"

typedef struct {
	int status;
	GtkWidget *button;
	GtkWidget *treeview;
	pthread_t thread;
	Queue queue;
} Sniff;

#endif
