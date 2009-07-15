#include <gtk/gtk.h>
#include <stdlib.h>
#include <assert.h>
#include "comman.h"
#include "dbb.h"
#include "file_menu.h"

#define BUILDER_XML_FILE "dbb.xml"

#define DEFAULT_DATABASE "data/default.db"

int main(int argc, char *argv[])
{
	DataBaseBuilder *dbb;

	/* allocate memory need by DataBaseBuilder struct *dbb */
	dbb = g_slice_new(DataBaseBuilder);

	/* initialize gtk+ libraries */
	gtk_init(&argc, &argv);

	/* initialize data in struct */
	init_data(dbb);

	/* initialize gui*/
	if( !init_gui(dbb) )	//error loading gui
		exit(1);

	/* show the window */
	gtk_widget_show(dbb->window);

	/* select wich database to edit, or open a new database */
	start(dbb);

	/* enter gtk main loop */
	gtk_main();

	/* free the memory allocated for DataBaseBuilder *dbb */
	g_slice_free(DataBaseBuilder, dbb);

	exit(0);
}

/* initialize DataBaseBuilder struct *dbb /
 set default value of data in struct*/
void init_data(DataBaseBuilder *dbb)
{
	dbb->title = (char *) malloc(sizeof(char) * MAX_LENGTH);
	sprintf(dbb->title, "%s", PROG_TITLE);
	dbb->database_name = NULL;
	dbb->new_db = FALSE;
	dbb->need_saved = FALSE;
}

gboolean init_gui(DataBaseBuilder *dbb)
{
	GtkBuilder *builder;
	GError *err = NULL;

	/* use  GtkBuilder to build GUI from xml file */
	builder = gtk_builder_new();
	if(gtk_builder_add_from_file(builder, BUILDER_XML_FILE, &err) == 0)
	{
		g_print("gtkbuilder reading xml file error\n");
		return FALSE;
	}

	/* get the widgets which will be referenced in callbacks */
	dbb->window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
	gtk_window_set_title(GTK_WINDOW(dbb->window), dbb->title);

	/* connect signals, passing DataBaseBuilder struct as usr_data */
	gtk_builder_connect_signals(builder, dbb);

	/* free memory used by GtkBuilder */
	g_object_unref(G_OBJECT(builder));

	return TRUE;
}


/* to select database */
static gboolean inited = FALSE;
/* to decalare thos as golal variable seems not a good idea/
 but put it in a gobal struct is even more worse /
 define a struct to svae them may be better */
static GtkWidget *start_window;
static GtkWidget *radio_button_new;
static GtkWidget *radio_button_open;
static GtkWidget *radio_button_new_from_default;
static GtkWidget *radio_button_open_default;

gboolean on_start_window_delete_event(GtkWidget *window, GdkEvent *event, DataBaseBuilder *dbb)
{
	g_print("DEBUG: on start window delete\n");

	if (!inited)
	{
		on_file_new_activate(NULL, dbb);
		g_print("DEBUG: initialed\n");
	}
	gtk_main_quit();

//	g_print("DEBUG: what's up?\n");

	return FALSE;
	/* i need to destroy the manually, otherwise,/
	   i need clicked the button for twice to close the start_window /
	 don't know why */
//	gtk_widget_destroy(start_window);
}

void on_button_cancel_clicked(GtkButton *button_cancel, DataBaseBuilder *dbb)
{
	g_print("DEBUG: on button cancle clicked\n");

//	on_start_window_delete_event(start_window, NULL, dbb);

	
	if (!inited)
	{
		on_file_new_activate(NULL, dbb);
		inited = TRUE;
		g_print("DEBUG: initialed\n");
	}
	gtk_main_quit();


	g_print("DEBUG: what's up?\n");
	/* i need to destroy the manually, otherwise,/
	   i need clicked the button for twice to close the start_window /
	 don't know why */
	gtk_widget_destroy(start_window);
}


void on_button_ok_clicked(GtkButton *button_ok, DataBaseBuilder *dbb)
{
	g_print("DEBUG: on button ok clicked\n");

	/* the argument type should be 'GtkToggleButton', and 'GtkRadioButton' is inherited form it */
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (radio_button_new)))
	{
		g_print("DEBUG: 1\n");
		on_file_new_activate(NULL, dbb);
	}
	else if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radio_button_open)))
	{
		g_print("DEBUG: 2\n");
		if (!on_file_open_activate(NULL, dbb))
		{	
			inited = FALSE;
			return;
		}
	}
	else if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radio_button_new_from_default)))
	{
		g_print("DEBUG: 3\n");
	}
	else if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radio_button_open_default)))
	{
		g_print("DEBUG: 4\n");
	}
	else
	{
		assert(FALSE);
	}

//	on_start_window_delete_event(start_window, NULL, dbb);
	
	inited = TRUE;
	gtk_main_quit();
	gtk_widget_destroy(start_window);
	
}

void start(DataBaseBuilder *dbb)
{
	//GtkWidget *start_window;
	GtkWidget *vbox;
	GtkWidget *frame;
	GtkWidget *vbbox;
	GtkWidget *hbox;

	GtkWidget *button_cancel;
	GtkWidget *button_ok;

	/* building gui */
	start_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(start_window), "Getting Start...");
	gtk_window_set_transient_for(GTK_WINDOW(start_window), GTK_WINDOW(dbb->window));
	gtk_window_set_position(GTK_WINDOW(start_window), GTK_WIN_POS_CENTER_ON_PARENT);
	gtk_container_set_border_width(GTK_CONTAINER(start_window), 10);

	vbox = gtk_vbox_new(FALSE, 2);
	gtk_container_add(GTK_CONTAINER(start_window), vbox);

	frame = gtk_frame_new("Open a database or create new one:");
	gtk_box_pack_start(GTK_BOX(vbox), frame, TRUE, TRUE, 0);

	vbbox = gtk_vbutton_box_new();
	gtk_container_set_border_width(GTK_CONTAINER(vbbox), 10);
	gtk_container_add(GTK_CONTAINER(frame), vbbox);

	hbox = gtk_hbox_new(FALSE, 2);
	gtk_box_pack_end(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	/* create first radio button */
	radio_button_new = gtk_radio_button_new_with_label(NULL, "Create a new database");
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_button_new), TRUE);
	gtk_box_pack_start(GTK_BOX(vbbox), radio_button_new, TRUE, TRUE, 5);

	/* create a radio button group from the radio button above */
	//group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio_button_new));

	radio_button_open = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio_button_new), "Open a Existed database");
	gtk_box_pack_start(GTK_BOX(vbbox), radio_button_open, TRUE, TRUE, 5);

	radio_button_new_from_default = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio_button_open), "Create a new database base on the default database use in character creator");
	gtk_box_pack_start(GTK_BOX(vbbox), radio_button_new_from_default, TRUE, TRUE, 5);

	radio_button_open_default = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio_button_new_from_default), "Open the default database used in character creator(NOT RECOMMAND)");
	gtk_box_pack_start(GTK_BOX(vbbox), radio_button_open_default, TRUE, TRUE, 5);

	button_ok = gtk_button_new_from_stock(GTK_STOCK_OK);
	gtk_box_pack_end(GTK_BOX(hbox), button_ok, FALSE, FALSE, 5);

	button_cancel = gtk_button_new_from_stock(GTK_STOCK_CANCEL);
	gtk_box_pack_end(GTK_BOX(hbox), button_cancel, FALSE, FALSE, 5);
	
	g_signal_connect(G_OBJECT(start_window), "delete-event", G_CALLBACK(on_start_window_delete_event), dbb);

	g_signal_connect(GTK_BUTTON(button_cancel), "clicked", G_CALLBACK(on_button_cancel_clicked), dbb);

	g_signal_connect(GTK_BUTTON(button_ok), "clicked", G_CALLBACK(on_button_ok_clicked), dbb);

	gtk_widget_show_all(start_window);

	//inited = TRUE;

	gtk_main();
}
