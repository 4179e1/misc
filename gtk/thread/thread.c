#include <gtk/gtk.h>

gboolean stat;

GtkWidget *label;
GtkWidget *progressbar;

void t1(gpointer data)
{
	int i;

	char msg[10];
	msg[9] = '\0';

	stat = TRUE;
	for (i = 1; i <= 100; i++)
	{
		if (!stat)
		{
			break;
		}

		g_message ("log%d", i);
		sprintf (msg, "log%d", i);

		gdk_threads_enter ();
		gtk_label_set_text (GTK_LABEL (label), msg);
		gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progressbar), (i/100.0));
		gdk_threads_leave ();

		g_usleep (100000);
	}
	
}

void start(gpointer widget, gpointer data)
{
	g_thread_create ((GThreadFunc)t1, NULL, FALSE, NULL);
}

void stop (gpointer widget, gpointer data)
{
	stat = FALSE;
}

int main (int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *button1;
	GtkWidget *button2;

	g_thread_init (NULL);
	gdk_threads_init ();
	gdk_threads_enter ();
	gtk_init (&argc, &argv);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

	vbox = gtk_vbox_new (TRUE, 2);
	gtk_container_add (GTK_CONTAINER (window), vbox);

	button1 = gtk_button_new_with_label ("starrrrrrrrrrrrrrrrrrt");
	gtk_box_pack_start_defaults (GTK_BOX (vbox), button1);

	button2 = gtk_button_new_with_label ("stop");
	gtk_box_pack_start_defaults (GTK_BOX (vbox), button2);

	label = gtk_label_new("abc");
	//gtk_label_set_text (GTK_LABEL (label), "nop");
	gtk_box_pack_start_defaults (GTK_BOX (vbox), label);

	progressbar = gtk_progress_bar_new ();
	gtk_box_pack_start_defaults (GTK_BOX (vbox), progressbar);

	g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit), NULL);

	g_signal_connect (GTK_BUTTON (button1), "clicked", G_CALLBACK (start), NULL);
	
	g_signal_connect (GTK_BUTTON (button2), "clicked", G_CALLBACK (stop), NULL);

	gtk_widget_show_all (window);

	gtk_main ();
	gdk_threads_leave ();

	return 0;
}
