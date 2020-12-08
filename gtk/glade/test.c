#include <gtk/gtk.h>
#include <glade/glade.h>
int main(int argc, char* argv[])
{
	GladeXML        *gxml;
	GtkWidget       *window;

	gtk_init (&argc, &argv);
	gxml = glade_xml_new ("test.glade", NULL, NULL);
	window = glade_xml_get_widget (gxml, "window");
	g_object_unref (G_OBJECT (gxml));
	gtk_widget_show(window);                
	gtk_main ();

	return 0;
}
