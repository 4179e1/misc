#include <gtk/gtk.h>
#include "gv1.h"
#include "genre.h"
#include "wrap.h"

struct _gv1
{
	GtkEntry *title;
	GtkEntry *artist;
	GtkEntry *album;
	GtkSpinButton *year;
	GtkEntry *comment;
	GtkSpinButton *track;
	GtkComboBox *genre;
};

Gv1 *gv1_new ()
{
	return g_new (Gv1, 1);
}

void gv1_free (Gv1 *gv1)
{
	g_free (gv1);
}

Gv1 *gv1_init (Gv1 *gv1, GtkBuilder *builder)
{
	GtkListStore *liststore;

	gv1->title = GTK_ENTRY (Gtk_builder_get_object (builder, "gv1_title"));
	gv1->artist = GTK_ENTRY (Gtk_builder_get_object (builder, "gv1_artist"));
	gv1->album = GTK_ENTRY (Gtk_builder_get_object (builder, "gv1_album"));
	gv1->year = GTK_SPIN_BUTTON (Gtk_builder_get_object (builder, "gv1_year"));
	gv1->comment = GTK_ENTRY (Gtk_builder_get_object (builder, "gv1_comment"));
	gv1->track = GTK_SPIN_BUTTON (Gtk_builder_get_object (builder, "gv1_track"));
	gv1->genre = GTK_COMBO_BOX (Gtk_builder_get_object (builder, "gv1_genre"));

	liststore = GTK_LIST_STORE (
			Gtk_builder_get_object (builder, "genre_list"));
	genre_list_init (liststore);

	gv1_reset (gv1);
	gv1_set_sensitive (gv1, FALSE);

	return gv1;
}

Gv1 *gv1_reset (Gv1 *gv1)
{
	gtk_entry_set_text (gv1->title, "");
	gtk_entry_set_text (gv1->artist, "");
	gtk_entry_set_text (gv1->album, "");
	gtk_spin_button_set_value (gv1->year, 1970.0);
	gtk_entry_set_text (gv1->comment, "");
	gtk_spin_button_set_value (gv1->track, 0.0);
	gtk_combo_box_set_active (gv1->genre, -1);
	
	return gv1;
}

Gv1 *gv1_set_sensitive (Gv1 *gv1, gboolean status)
{
	gtk_widget_set_sensitive (GTK_WIDGET (gv1->title), status);
	gtk_widget_set_sensitive (GTK_WIDGET (gv1->artist), status);
	gtk_widget_set_sensitive (GTK_WIDGET (gv1->album), status);
	gtk_widget_set_sensitive (GTK_WIDGET (gv1->year), status);
	gtk_widget_set_sensitive (GTK_WIDGET (gv1->comment), status);
	gtk_widget_set_sensitive (GTK_WIDGET (gv1->track), status);
	gtk_widget_set_sensitive (GTK_WIDGET (gv1->genre), status);
	return gv1;
}

Id3v1 *gv1_write_to_id3v1 (Gv1 *gv1, Id3v1 *tag)
{
	g_assert (gv1 != NULL);
	g_assert (tag != NULL);

	const gchar *title;
	const gchar *artist;
	const gchar *album;
	gdouble d_year;
	gchar year[ID3V1_YEAR_LEN];
	const gchar *comment;
	gchar track;
	gchar genre;

	title = gtk_entry_get_text (gv1->title);
	artist = gtk_entry_get_text (gv1->artist);
	album = gtk_entry_get_text (gv1->album);

	d_year = gtk_spin_button_get_value (gv1->track);
	g_ascii_dtostr (year, ID3V1_YEAR_LEN, d_year);

	comment = gtk_entry_get_text (gv1->comment);
	track = (gchar)gtk_spin_button_get_value (gv1->track);
	genre = gtk_combo_box_get_active (gv1->genre);

	id3v1_set_content_from_param (tag, title, artist, album,
			year, comment, &track, &genre);

	/* nothing need to free */
	return tag;
}

Gv1 *gv1_read_from_id3v1 (Gv1 *gv1, Id3v1 *tag)
{
	gchar *title;
	gchar *artist;
	gchar *album;
	gchar *year;
	gchar *comment;
	gchar track;
	gchar genre;

	id3v1_get_content_to_param (tag, &title, &artist,
			&album, &year, &comment,
			&track, &genre);

	gtk_entry_set_text (gv1->title, title);
	gtk_entry_set_text (gv1->artist, artist);
	gtk_entry_set_text (gv1->album, album);
	gtk_spin_button_set_value (gv1->year, g_ascii_strtod (year, NULL));
	gtk_entry_set_text (gv1->comment, comment);
	gtk_spin_button_set_value (gv1->track, (gdouble)track);
	if (genre_valid (genre))
	{
		gtk_combo_box_set_active (gv1->genre, genre);
	}
	else
	{
		gtk_combo_box_set_active (gv1->genre, -1);
	}

	g_free (title);
	g_free (artist);
	g_free (album);
	g_free (year);
	g_free (comment);

	return gv1;
}
