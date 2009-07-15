#include <gtk/gtk.h>

int main(int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *label;

	gchar *str = "<b>Cold was my soul</b>\n\
<big>Untold was the pain</big>\n\
<i>I faced when you left me</i>\n\
<s>A rose in the rain....</s>\n\
<sub>So I swore to the razor</sub>\n\
<sup>That never, enchained</sup>\n\
<small>Would your dark nails of faith</small>\n\
<tt>Be pushed through my veins again</tt>\n\
\n\
<u>Bared on your tomb</u>\n\
I'm a prayer for your loneliness\n\
And would you ever soon\n\
Come above onto me?\n\
For once upon a time\n\
On the binds of your lowliness\n\
I could always find the slot for your sacred key ";

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(window), 350, 400);

	label = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label), str);

	gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
	gtk_container_add(GTK_CONTAINER(window), label);

	g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), G_OBJECT(window));

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}
