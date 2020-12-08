#include <gtk/gtk.h>
#include <stdio.h>
#include "database_builder.h"
#include "new_file.h"
#include "handler.h"
#include "other.h"
#include "database.h"

#define DEFAULT_LOCATION "./data"
#define DEFAULT_DATABASE "./data/default/default.db"

gchar *open_file(DatabaseBuilder *builder)
{
	gchar *filename = NULL;

	filename = get_filename(builder);

	return filename;
}

gchar *get_filename(DatabaseBuilder *builder)
{
	NewFileWindow *nf;
	
	gchar *filename;

	nf = g_slice_new(NewFileWindow);

	/* builde new file window GUI */
	GtkWidget *new_file_window;
	GtkWidget *vbox;

	GtkWidget *check_button_source;

	GtkWidget *hbox_name;
	GtkWidget *label_name;
	GtkWidget *entry_name;

	GtkWidget *check_button_location;

	GtkWidget *hbox_location;
	GtkWidget *label_location;
	GtkWidget *entry_location;
	GtkWidget *button_browse;

	GtkWidget *hbox_button;
	GtkWidget *button_cancel;
	GtkWidget *button_save;

	new_file_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (new_file_window), "Create new database");
	gtk_window_set_transient_for (GTK_WINDOW (new_file_window), GTK_WINDOW (builder->window));
	gtk_window_set_position (GTK_WINDOW (new_file_window), GTK_WIN_POS_CENTER_ON_PARENT);
	gtk_window_set_destroy_with_parent (GTK_WINDOW (new_file_window), TRUE);
	gtk_window_set_resizable (GTK_WINDOW (new_file_window), FALSE);
	gtk_window_set_modal (GTK_WINDOW (new_file_window), TRUE);

	vbox = gtk_vbox_new(TRUE, 15);
	gtk_container_set_border_width (GTK_CONTAINER (vbox), 10);
	gtk_container_add (GTK_CONTAINER (new_file_window), vbox);

	check_button_source = gtk_check_button_new_with_label ("Import content of default database");
	gtk_box_pack_start (GTK_BOX (vbox), check_button_source, FALSE, FALSE, 5);

	hbox_name = gtk_hbox_new(FALSE, 2);
	gtk_box_pack_start (GTK_BOX(vbox), hbox_name, FALSE, FALSE, 5);
	
	label_name = gtk_label_new ("Database name: ");
	entry_name = gtk_entry_new();
	gtk_box_pack_start (GTK_BOX(hbox_name), label_name, FALSE, FALSE, 2);
	gtk_box_pack_start (GTK_BOX(hbox_name), entry_name, TRUE, TRUE, 2);

	check_button_location = gtk_check_button_new_with_label ("Use default location");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (check_button_location), TRUE);
	gtk_box_pack_start (GTK_BOX(vbox), check_button_location, FALSE, FALSE, 5);

	hbox_location = gtk_hbox_new(FALSE, 2);
	gtk_box_pack_start (GTK_BOX (vbox), hbox_location, FALSE, FALSE, 5);

	label_location = gtk_label_new ("Location: ");
	entry_location = gtk_entry_new();
	gtk_entry_set_text (GTK_ENTRY (entry_location), DEFAULT_LOCATION); 
	button_browse = gtk_button_new_with_mnemonic ("_Browse");
	gtk_box_pack_start (GTK_BOX (hbox_location), label_location, FALSE, FALSE, 2);
	gtk_box_pack_start (GTK_BOX (hbox_location), entry_location, TRUE, TRUE, 2);
	gtk_box_pack_start (GTK_BOX (hbox_location), button_browse, FALSE, FALSE, 2);

	hbox_button = gtk_hbox_new(FALSE, 2);
	gtk_box_pack_start (GTK_BOX (vbox), hbox_button, FALSE, FALSE, 2);

	button_save = gtk_button_new_from_stock (GTK_STOCK_SAVE);
	button_cancel = gtk_button_new_from_stock (GTK_STOCK_CANCEL);
	gtk_box_pack_end (GTK_BOX (hbox_button), button_save, FALSE, FALSE, 0);
	gtk_box_pack_end (GTK_BOX (hbox_button), button_cancel, FALSE, FALSE, 20);

	gtk_widget_set_sensitive (GTK_WIDGET (entry_location), FALSE);
	gtk_widget_set_sensitive (GTK_WIDGET (button_browse), FALSE);
	gtk_widget_set_sensitive (GTK_WIDGET (button_save), FALSE);

	nf->new_file_window = new_file_window;
	nf->check_button_source = check_button_source;
	nf->entry_name = entry_name;
	nf->check_button_location = check_button_location;
	nf->entry_location = entry_location;
	nf->button_browse = button_browse;
	nf->button_cancel = button_cancel;
	nf->button_save = button_save;
	nf->filename = NULL;

	g_signal_connect_swapped (G_OBJECT (new_file_window), "destroy",
							  G_CALLBACK (gtk_main_quit), G_OBJECT (new_file_window));
//	g_signal_connect (GTK_WIDGET (new_file_window), "delete-event", G_CALLBACK (on_window_delete), NULL);

	g_signal_connect (GTK_EDITABLE (entry_name), "changed",
					  G_CALLBACK (on_entry_name_changed), nf);
	g_signal_connect (GTK_BUTTON (button_browse), "clicked",
					  G_CALLBACK (on_button_browse_clicked), nf);
	g_signal_connect (GTK_BUTTON (check_button_location), "clicked",
					  G_CALLBACK (on_check_button_location_clicked), nf);
	g_signal_connect (GTK_BUTTON (button_cancel), "clicked",
					  G_CALLBACK (on_button_cancel_clicked), nf);
	g_signal_connect (GTK_BUTTON (button_save), "clicked",
					  G_CALLBACK (on_button_save_clicked), nf);

	gtk_widget_show_all (new_file_window);

	gtk_main();
	
	filename = nf->filename;
	g_slice_free(NewFileWindow, nf);

	return filename;
}

void on_entry_name_changed (GtkEditable *entry_name, NewFileWindow *nf)
{
	const gchar *name;

	name = gtk_entry_get_text (GTK_ENTRY (nf->entry_name));

	if (g_str_equal("", name))
	{
		gtk_widget_set_sensitive (GTK_WIDGET (nf->button_save), FALSE);
	}
	else
	{
		gtk_widget_set_sensitive (GTK_WIDGET (nf->button_save), TRUE);
	}

}
void on_check_button_location_clicked (GtkButton *button_location, NewFileWindow *nf)
{
	gboolean status;

	status = (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (nf->check_button_location)));

	
	if (status)
	{
		gtk_widget_set_sensitive (GTK_WIDGET (nf->entry_location), FALSE);
		gtk_widget_set_sensitive (GTK_WIDGET (nf->button_browse), FALSE);
		gtk_entry_set_text (GTK_ENTRY (nf->entry_location), DEFAULT_LOCATION);
	}
	else
	{
		gtk_widget_set_sensitive (GTK_WIDGET (nf->entry_location), TRUE);
		gtk_widget_set_sensitive (GTK_WIDGET (nf->button_browse), TRUE);
	}

}
void on_button_browse_clicked (GtkButton *button_browse, NewFileWindow *nf)
{
	gchar *location;

	location = get_location(nf);

	if (NULL == location)
	{
		gtk_entry_set_text (GTK_ENTRY (nf->entry_location), DEFAULT_LOCATION);
	}
	else
	{
		gtk_entry_set_text (GTK_ENTRY (nf->entry_location), location);
	}
}

void on_button_cancel_clicked (GtkButton *button_cancel, NewFileWindow *nf)
{
	gtk_widget_destroy(GTK_WIDGET(nf->new_file_window));
	gtk_main_quit();
}

void on_button_save_clicked (GtkButton *button_save, NewFileWindow *nf)
{
	const gchar *name;
	const gchar *location;
	gchar *file;
	gboolean inited = FALSE;

	name = gtk_entry_get_text (GTK_ENTRY (nf->entry_name));
	location = gtk_entry_get_text (GTK_ENTRY (nf->entry_location));

	if ( g_str_equal ("", location))
	{
		file = g_strdup_printf ("%s/%s", DEFAULT_LOCATION, name);
	}
	else
	{
		file = g_strdup_printf ("%s/%s", location, name);
	}

	/* if file exist */
	if (file_exists(file))
	{
		/*
		   ask user overwiret the old existed file or not.
		   in fact, the overwirte is simplely delete the old file and create a new one,
		   it's not a good style but it's the simplest way.
		*/
		if (check ("File existed, do you want to overwrite?"))
		{
			/* if anwser is YES, removge the old existed file */
			if(remove (file) != 0)
			{
				error_message ("Error: Overwrite fail, cannot delete old file\n");
				return;
			}		

		}
		else	/* if answer isn't YES, return & let user input again */
		{
			g_free (file);
			return;
		}
	}

	/* create an new empty file */
	if(!create_file (file))
	{
		error_message ("Error: Overwirte fail, cannot create new file\n");
		return;
	}

	/* 
	   if check button 'use content of default database' selected, 
	   we should copy the default database to the new file.
	   in fact, the 'usr content of default database' is simplely copy the 
	   default database to the new empty file; the instrument above has
	   make sure that the new file is an empty file.
	*/
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (nf->check_button_source)))
	{
		if (copy_file (file, DEFAULT_DATABASE))
		{
			inited = TRUE;
		}
		else
		{
			error_message ("Error: cannot copy default database to new file");
			return;
		}
	}

	if (!inited)
	{
		if (!init_database (file))
		{
			error_message ("Error: cannot initialize database");
			return;
		}
	}

	nf->filename = file;

	gtk_widget_destroy(nf->new_file_window);
	gtk_main_quit();

}

gchar *get_location(NewFileWindow *nf)
{
	GtkWidget	*chooser;
	gchar		*location = NULL;

	chooser = gtk_file_chooser_dialog_new ("Selection Directory...",
			GTK_WINDOW (nf->new_file_window),
			GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
			GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
			GTK_STOCK_OK, GTK_RESPONSE_OK,
			NULL);
	if (GTK_RESPONSE_OK == (gtk_dialog_run (GTK_DIALOG (chooser))))
	{
		location = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (chooser));
	}
	gtk_widget_destroy (chooser);

	return location;
}
