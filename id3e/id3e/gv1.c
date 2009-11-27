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

	GtkToggleButton *ck_artist;
	GtkToggleButton *ck_album;
	GtkToggleButton *ck_year;
	GtkToggleButton *ck_comment;
	GtkToggleButton *ck_genre;
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

	gv1->ck_artist = GTK_TOGGLE_BUTTON (Gtk_builder_get_object (builder, "ck_artist"));
	gv1->ck_album = GTK_TOGGLE_BUTTON (Gtk_builder_get_object (builder, "ck_album"));
	gv1->ck_year = GTK_TOGGLE_BUTTON (Gtk_builder_get_object (builder, "ck_year"));
	gv1->ck_comment = GTK_TOGGLE_BUTTON (Gtk_builder_get_object (builder, "ck_comment"));
	gv1->ck_genre = GTK_TOGGLE_BUTTON (Gtk_builder_get_object (builder, "ck_genre"));

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

void gv1_write_to_id3v1_multi (Gv1 *gv1, Id3v1Multi *mul)
{
	g_assert (gv1 != NULL);
	g_assert (mul != NULL);

	if (gtk_toggle_button_get_active (gv1->ck_artist))
	{
		id3v1_multi_set_artist (mul, gtk_entry_get_text (gv1->artist));
	}
	else
	{
		id3v1_multi_set_artist (mul, NULL);
	}

	if (gtk_toggle_button_get_active (gv1->ck_album))
	{
		id3v1_multi_set_album (mul, gtk_entry_get_text (gv1->album));
		/* DEBUG */
	}
	else
	{
		id3v1_multi_set_album (mul, NULL);
	}

	if (gtk_toggle_button_get_active (gv1->ck_year))
	{
		/* require an additioanl '\0' */
		gchar year[ID3V1_YEAR_LEN + 1];
		gdouble d_year = gtk_spin_button_get_value (gv1->year);
		g_ascii_dtostr (year, sizeof(year), d_year);
		id3v1_multi_set_year (mul, year);
		/* DEBUG */
	}
	else
	{
		id3v1_multi_set_year (mul, NULL);
	}

	if (gtk_toggle_button_get_active (gv1->ck_comment))
	{
		id3v1_multi_set_comment (mul, gtk_entry_get_text (gv1->comment));
	}
	else
	{
		id3v1_multi_set_comment (mul, NULL);
	}

	if (gtk_toggle_button_get_active (gv1->ck_genre))
	{
		gchar genre = gtk_combo_box_get_active (gv1->genre);
		id3v1_multi_set_genre (mul, &genre);
	}
	else
	{
		id3v1_multi_set_genre (mul, NULL);
	}
}

void gv1_read_from_id3v1_multi (Gv1 *gv1, Id3v1Multi *mul)
{
	gchar *artist;
	gchar *album;
	gchar *year;
	gchar *comment;
	gchar genre_val;
	gchar *genre = &genre_val;

	id3v1_multi_get_content_to_param (mul, &artist, &album, &year, &comment, &genre);

	if (artist)
	{
		gtk_entry_set_text (gv1->artist, artist);
		gtk_toggle_button_set_active (gv1->ck_artist, TRUE);
		g_free (artist);
	}
	else
	{
		gtk_toggle_button_set_active (gv1->ck_artist, FALSE);
	}

	if (album)
	{
		gtk_entry_set_text (gv1->album, album);
		gtk_toggle_button_set_active (gv1->ck_album, TRUE);
		g_free (album);
	}
	else
	{
		gtk_toggle_button_set_active (gv1->ck_album, FALSE);
	}

	if (year)
	{
		gtk_spin_button_set_value (gv1->year, g_ascii_strtod (year, NULL));
		gtk_toggle_button_set_active (gv1->ck_year, TRUE);
		g_free (year);
	}
	else
	{
		gtk_toggle_button_set_active (gv1->ck_year, FALSE);
	}

	if (comment)
	{
		gtk_entry_set_text (gv1->comment, comment);
		gtk_toggle_button_set_active (gv1->ck_comment, TRUE);
		g_free (comment);
	}
	else
	{
		gtk_toggle_button_set_active (gv1->ck_comment, FALSE);
	}

	if (genre)
	{
		if (genre_valid (*genre))
		{
			gtk_combo_box_set_active (gv1->genre, *genre);
		}
		else
		{
			gtk_combo_box_set_active (gv1->genre, -1);
		}
		gtk_toggle_button_set_active (gv1->ck_genre, TRUE);
	}
	else
	{
		gtk_toggle_button_set_active (gv1->ck_genre, TRUE);
	}
}
