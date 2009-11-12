#include <gtk/gtk.h>
#include <string.h>
#include "id3v1.h"
#include "wrap.h"

#define FILE_MODE "rb+"
#define ID3V1_LEN 128
#define ID3V1_POS (-ID3V1_LEN)

struct _id3v1
{
	gchar tag[ID3V1_TAG_LEN];
	gchar title[ID3V1_TITLE_LEN];
	gchar artist[ID3V1_ARTIST_LEN];
	gchar album[ID3V1_ALBUM_LEN];
	gchar year[ID3V1_YEAR_LEN];
	gchar comment[ID3V1_COMMENT_LEN];
	gchar padding;
	gchar track;
	gchar genre;
};

/* mem */
Id3v1 *id3v1_new (void)
{
	Id3v1 *tag;
	tag =  g_new0 (Id3v1, 1);
	return tag;
}

void id3v1_free (Id3v1 *id3v1)
{
	g_free (id3v1);
}

Id3v1 *id3v1_new_from_path (const gchar *path)
{
	FILE *file;
	Id3v1 *tag;

	file = Fopen (path, FILE_MODE);
	tag = id3v1_new_from_file (file);
	Fclose (file);

	return tag;
}

Id3v1 *id3v1_new_from_file (FILE *file)
{
	Id3v1 *tag;

	tag = id3v1_new ();
	if (id3v1_read_tag_from_file (tag, file))
	{
		return tag;
	}
	else
	{
		g_free (tag);
		return NULL;
	}
}

/* file operation */
gboolean id3v1_path_have_tag (const gchar *path)
{
	FILE *file;
	gboolean result;

	file = Fopen (path, FILE_MODE);
	result = id3v1_file_have_tag (file);
	Fclose (file);

	return result;
}

gboolean id3v1_read_tag_from_path (Id3v1 *tag, const gchar *path)
{
	FILE *file;
	gboolean result;
	
	file = Fopen (path, FILE_MODE);
	result = id3v1_read_tag_from_file (tag, file);
	Fclose (file);

	return result;
}

gboolean id3v1_write_tag_to_path (const Id3v1 *tag, const gchar *path)
{
	FILE *file;
	gboolean result;

	file = Fopen (path, FILE_MODE);
	result = id3v1_write_tag_to_file (tag, file);
	Fclose (file);

	return result;
}

gboolean Id3v1_remove_tag_from_path (const gchar *path)
{
	FILE *file;
	gboolean result;

	file = Fopen (path, FILE_MODE);
	result = id3v1_remove_tag_from_file (file);
	Fclose (file);

	return FALSE;
}

gboolean id3v1_file_have_tag (FILE *file)
{
	gchar tmp[ID3V1_TAG_LEN + 1];
	tmp[ID3V1_TAG_LEN] = '\0';

	if (Fseek (file, ID3V1_POS, SEEK_END) != 0)
	{
		return FALSE;
	}

	Efread (tmp, ID3V1_TAG_LEN, 1, file);

	if (strncmp (tmp, ID3V1_TAG, ID3V1_TAG_LEN) == 0)
	{
		return TRUE;
	}

	return FALSE;
}

gboolean id3v1_read_tag_from_file (Id3v1 *tag,  FILE *file)
{
	gboolean result;

	if (!id3v1_file_have_tag (file))
	{
		return FALSE;
	}

	Fseek (file, ID3V1_POS, SEEK_END);

	/*FIXME: would Efread (tag, ID3V1_LEN, 1, file) work? */
	result = Efread (&tag, ID3V1_LEN, 1, file);

	/* if not, using following instead */
#if 0
	Efread (tag->tag, ID3V1_TAG_LEN, 1, file);
	Efread (tag->title, ID3V1_TITLE_LEN, 1, file);
	Efread (tag->artist, ID3V1_ARTIST_LEN, 1, file);
	Efread (tag->album, ID3V1_ALBUM_LEN, 1, file);
	Efread (tag->year, ID3V1_YEAR_LEN, 1, file);
	Efread (tag->comment, ID3V1_COMMENT_LEN, 1, file);
	Efread (&(tag->track), ID3V1_TRACK_LEN, 1, file);
	Efread (&(tag->genre), ID3V1_GENRE_LEN, 1, file);
#endif
	return result;
}

gboolean id3v1_write_tag_to_file (const Id3v1 *tag, FILE *file)
{
	gboolean result;

	if (id3v1_file_have_tag (file))
	{
		Fseek (file, ID3V1_POS, SEEK_END);
	}
	else
	{
		Fseek (file, 0, SEEK_END);
	}

	/*FIXME: would Efwrite (tag, ID3V1_LEN, 1, file) work? */
	result = Ewrite (&tag, ID3V1_LEN, 1, file);

	/* if not, using following instead */
#if 0
	Efwrite (tag->tag, ID3V1_TAG_LEN, 1, file);
	Efwrite (tag->title, ID3V1_TITLE_LEN, 1, file);
	Efwrite (tag->artist, ID3V1_ARTIST_LEN, 1, file);
	Efwrite (tag->album, ID3V1_ALBUM_LEN, 1, file);
	Efwrite (tag->year, ID3V1_YEAR_LEN, 1, file);
	Efwrite (tag->comment, ID3V1_COMMENT_LEN, 1, file);
	Efwrite (&(tag->track), ID3V1_TRACK_LEN, 1, file);
	Efwrite (&(tag->genre), ID3V1_GENRE_LEN, 1, file);
#endif
	return result;
}

gboolean id3v1_remove_tag_from_file (FILE *file)
{
	if (!id3v1_file_have_tag (file))
	{
		return TRUE;
	}
	/* FIXME: if have tag, how to remove? */
	return FALSE;
}
/* structure operation */
gchar *id3v1_get_title (Id3v1 *tag)
{
	return g_strndup (tag->title, ID3V1_TITLE_LEN);
}

gchar *id3v1_get_artist (Id3v1 *tag)
{
	return g_strndup (tag->artist, ID3V1_ARTIST_LEN);
}

gchar *id3v1_get_album (Id3v1 *tag)
{
	return g_strndup (tag->album, ID3V1_ALBUM_LEN);
}

gchar *id3v1_get_year (Id3v1 *tag) 
{
	return g_strndup (tag->year, ID3V1_YEAR_LEN);
}

gchar *id3v1_get_comment (Id3v1 *tag)
{
	return tag->comment;
}

gchar id3v1_get_track (Id3v1 *tag)
{
	return tag->track;
}

gchar id3v1_get_genre (Id3v1 *tag) {
	return tag->genre;
}

void id3v1_set_title (Id3v1 *tag, gchar *title)
{
	memset (tag->title, 0, ID3V1_TITLE_LEN);
	if (title != NULL)
	{
		strncpy (tag->title, title, ID3V1_TITLE_LEN);
	}
}

void id3v1_set_artist (Id3v1 *tag, gchar *artist)
{
	memset (tag->artist, 0, ID3V1_ARTIST_LEN);
	if (artist != NULL)
	{
		strncpy (tag->artist, artist, ID3V1_ARTIST_LEN);
	}
}

void id3v1_set_album (Id3v1 *tag, gchar *album)
{
	memset (tag->album, 0, ID3V1_ALBUM_LEN);
	if (album != NULL)
	{
		strncpy (tag->album, album, ID3V1_ALBUM_LEN);
	}
}


void id3v1_set_year (Id3v1 *tag, gchar *year)
{
	memset (tag->year, 0, ID3V1_YEAR_LEN);
	if (year != NULL)
	{
		strncpy (tag->year, year, ID3V1_YEAR_LEN);
	}
}


void id3v1_set_comment (Id3v1 *tag, gchar *comment)
{
	memset (tag->comment, 0, ID3V1_COMMENT_LEN);
	if (comment != NULL)
	{
		strncpy (tag->comment, comment, ID3V1_COMMENT_LEN);
	}
}


void id3v1_set_track (Id3v1 *tag, gchar track)
{
	tag->track = track;
}


void id3v1_set_genre (Id3v1 *tag, gchar genre)
{
	tag->genre = genre;
}

Id3v1 *id3v1_get_content_to_param (Id3v1 *tag, gchar**title, 
		gchar **artist, gchar **album, gchar **year, 
		gchar **comment, gchar *track, gchar *genre)
{
	if (title)
	{
		*title = g_strndup (tag->title, ID3V1_TITLE_LEN);
	}
	if (artist)
	{
		*artist = g_strndup (tag->artist, ID3V1_ARTIST_LEN);
	}
	if (album)
	{
		*album = g_strndup (tag->album, ID3V1_ALBUM_LEN);
	}
	if (year)
	{
		*year = g_strndup (tag->year, ID3V1_YEAR_LEN);
	}
	if (comment)
	{
		*comment = g_strndup (tag->comment, ID3V1_COMMENT_LEN);
	}
	if (track)
	{
		*track = tag->track;
	}
	if (genre)
	{
		*genre = tag->genre;
	}

	return tag;
}

Id3v1 *id3v1_set_content_from_param (Id3v1 *tag,
		gchar *title, gchar *artist, gchar *album,
		gchar *year, gchar *comment, gchar *track, gchar *genre)
{
	if (title)
	{
		id3v1_set_title (tag, title);
	}
	if (artist)
	{
		id3v1_set_artist (tag, artist);
	}
	if (album)
	{
		id3v1_set_album (tag, album);
	}
	if (year)
	{
		id3v1_set_year (tag, year);
	}
	if (track)
	{
		tag->track = *track;
	}
	if (genre)
	{
		tag->genre = *genre;
	}

	return tag;
}
