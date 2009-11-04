#include <gtk/gtk.h>
#include <unistd.h>

gboolean stat;

GtkWidget *label;

void t1(gpointer data)
{
	int i;

	char msg[10];
	msg[9] = '\0';

	stat = TRUE;
	for (i = 0; i < 100; i++)
	{
		if (!stat)
		{
			break;
		}

		g_message ("log%d", i);
		sprintf (msg, "log%d", i);
		gtk_label_set_text (GTK_LABEL (label), msg);
		sleep (1);
	}
	
}

void start(gpointer widget, gpointer data)
{
	g_thread_create (t1, NULL, FALSE, NULL);
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

	g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit), NULL);

	g_signal_connect (GTK_BUTTON (button1), "clicked", G_CALLBACK (start), NULL);
	
	g_signal_connect (GTK_BUTTON (button2), "clicked", G_CALLBACK (stop), NULL);

	gtk_widget_show_all (window);

	gtk_main ();

	return 0;
}
