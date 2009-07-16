#include <gtk/gtk.h>
#include  <unistd.h>   
#include <pthread.h>
#include <stdlib.h>

int i;
double value = 0.1;

static int a = 0;
static	pthread_t thread;

gboolean timeout_callback (gpointer progressbar) {
	printf ("set progressbar\n");
	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progressbar), value * i);
	return TRUE;
}

static void *thread_function (void *progressbar) {
//	int i;

	a = 0;

	gint timer;

	timer = g_timeout_add (1000, timeout_callback, (gpointer)progressbar);


//	double value = 0.1;
	for (i = 1; i <= 10; i ++) {
		if (a != 0)
		{
			break;
		}

		g_print ("%d\n", i);
//		gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR (progressbar), value * i);
//		gdk_flush ();
//		sleep (1);
	}

	g_source_remove (timer);

	return ((void *) 0);
}

static void on_button_start_clicked (GtkButton *button, GtkProgressBar *progressbar) {

	if (pthread_create (&thread, NULL, thread_function, (void *)progressbar)) {
		fprintf (stderr, "error creating thread\n");
		exit (1);
	}

	/*

*/
}

static void on_button_stop_clicked (GtkButton *button, gpointer userdata) {
	a = 1;

	if (pthread_join (thread, NULL)) {
		fprintf (stderr, "error joining thread\n");
		exit (1);
	}
}

int main (int argc, char *argv[]) {
	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *button_start;
	GtkWidget *button_stop;
	GtkWidget *progressbar;
	
	gtk_init (&argc, &argv);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

	vbox = gtk_vbox_new(TRUE, 2);
	gtk_container_add (GTK_CONTAINER (window), vbox);

	button_start = gtk_button_new_with_label ("Start");
	gtk_box_pack_start_defaults (GTK_BOX (vbox), button_start);

	button_stop = gtk_button_new_with_label ("Stop");
	gtk_box_pack_start_defaults (GTK_BOX (vbox), button_stop);

	progressbar = gtk_progress_bar_new ();
	gtk_box_pack_start_defaults (GTK_BOX (vbox), progressbar);

	g_signal_connect_swapped (G_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit), G_OBJECT (window));

	g_signal_connect (GTK_BUTTON (button_start), "clicked", G_CALLBACK (on_button_start_clicked), GTK_PROGRESS_BAR (progressbar));

	g_signal_connect (GTK_BUTTON (button_stop), "clicked", G_CALLBACK (on_button_stop_clicked), NULL);

	gtk_widget_show_all (window);

	gtk_main();

	return 0;
}
