#include <gtk/gtk.h>
#include <string.h>
#include "id3v1.h"
#include "wrap.h"

#define FILE_MODE "rb+"

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

/* meme */
Id3v1 *id3v1_new (void)
{
	Id3v1 *tag;
	tag =  g_new0 (Id3v1, 1);
	strncpy (tag->tag, ID3V1_TAG, ID3V1_TAG_LEN);
	return tag;
}

void id3v1_free (Id3v1 *id3v1)
{
	g_free (id3v1);
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

Id3v1 *id3v1_read_tag_from_path (const gchar *path, Id3v1 *tag)
{
	return tag;
}
gboolean id3v1_write_tag_to_path (const Id3v1 *tag, const gchar *path)
{
	return FALSE;
}
gboolean Id3v1_remove_tag_from_path (const gchar *path)
{
	return FALSE;
}

gboolean id3v1_file_have_tag (FILE *file)
{
	gchar tmp[ID3V1_TAG_LEN + 1];
	tmp[ID3V1_TAG_LEN] = '\0';

	if (Fseek (file, -128, SEEK_END) != 0)
	{
		return FALSE;
	}

	fread (tmp, 3, 1, file);

	if (strncmp (tmp, ID3V1_TAG, ID3V1_TAG_LEN) == 0)
	{
		return TRUE;
	}

	return FALSE;
}

Id3v1 *id3v1_read_tag_from_file (FILE *file, Id3v1 *tag)
{
	return tag;
}
gboolean id3v1_write_tag_to_file (const Id3v1 *tag, FILE *file)
{
	return FALSE;
}
gboolean id3v1_remove_tag_from_file (FILE *file)
{
	return FALSE;
}
/* structure operation */
const gchar *id3v1_get_title (Id3v1 *tag)
{
	return tag->title;
}

const gchar *id3v1_get_artist (Id3v1 *tag)
{
	return tag->artist;
}

const gchar *id3v1_get_album (Id3v1 *tag)
{
	return tag->album;
}

const gchar *id3v1_get_year (Id3v1 *tag) 
{
	return tag->year;
}

const gchar *id3v1_get_comment (Id3v1 *tag)
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

const gchar *id3v1_set_title (Id3v1 *tag, gchar *title)
{
	memset (tag->title, 0, ID3V1_TITLE_LEN);
	if (title != NULL)
	{
		strncpy (tag->title, title, ID3V1_TITLE_LEN);
	}
	return tag->title;
}

const gchar *id3v1_set_artist (Id3v1 *tag, gchar *artist)
{
	memset (tag->artist, 0, ID3V1_ARTIST_LEN);
	if (artist != NULL)
	{
		strncpy (tag->artist, artist, ID3V1_ARTIST_LEN);
	}
	return tag->artist;
}

const gchar *id3v1_set_album (Id3v1 *tag, gchar *album)
{
	memset (tag->album, 0, ID3V1_ALBUM_LEN);
	if (album != NULL)
	{
		strncpy (tag->album, album, ID3V1_ALBUM_LEN);
	}
	return tag->album;
}


const gchar *id3v1_set_year (Id3v1 *tag, gchar *year)
{
	memset (tag->year, 0, ID3V1_YEAR_LEN);
	if (year != NULL)
	{
		strncpy (tag->year, year, ID3V1_YEAR_LEN);
	}
	return tag->year;
}


const gchar *id3v1_set_comment (Id3v1 *tag, gchar *comment)
{
	memset (tag->comment, 0, ID3V1_COMMENT_LEN);
	if (comment != NULL)
	{
		strncpy (tag->comment, comment, ID3V1_COMMENT_LEN);
	}
	return tag->comment;
}


gchar id3v1_set_track (Id3v1 *tag, gchar track)
{
	tag->track = track;
	return tag->track;
}


gchar id3v1_set_genre (Id3v1 *tag, gchar genre)
{
	tag->genre = genre;
	return tag->genre;
}

Id3v1 *id3v1_get_content_to_param (Id3v1 *tag, const gchar**title, 
		const gchar **artist, const gchar **album, const gchar **year, 
		const gchar **comment, gchar *track, gchar *genre)
{
	if (title)
	{
		*title = tag->title;
	}
	if (artist)
	{
		*artist = tag->artist;
	}
	if (album)
	{
		*album = tag->album;
	}
	if (year)
	{
		*year = tag->year;
	}
	if (comment)
	{
		*comment = tag->comment;
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
		id3v1_set_track (tag, *track);
	}
	if (genre)
	{
		id3v1_set_genre (tag, *genre);
	}

	return tag;
}
