#include <gtk/gtk.h>
#include <pthread.h>
#include <stdlib.h>
#include "icmp.h"
#include "stop.h"

void on_stop_clicked (GtkButton *button, gpointer data) {

	Icmp *icmp = (Icmp *)data;

	if (icmp->status != 0) {
		icmp->status = 0;
	
		if (pthread_join (icmp->thread, NULL)) {
			fprintf (stderr, "Error joining thread\n");
			exit (1);
		}
	}
}
