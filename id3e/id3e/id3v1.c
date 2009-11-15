#include <gtk/gtk.h>
#include <string.h>
#include "id3v1.h"
#include "wrap.h"

#define FILE_MODE "rb+"
#define DUMP_MODE "wb+"
#define ID3V1_LEN 128
#define ID3V1_POS (-ID3V1_LEN)

struct _id3v1
{
	gchar tag[ID3V1_TAG_LEN];			/* 3	3	*/
	gchar title[ID3V1_TITLE_LEN];		/* 30	33	*/
	gchar artist[ID3V1_ARTIST_LEN];		/* 30	63	*/
	gchar album[ID3V1_ALBUM_LEN];		/* 30	93	*/
	gchar year[ID3V1_YEAR_LEN];			/* 4	97	*/
	gchar comment[ID3V1_COMMENT_LEN];	/* 28	125	*/
	gchar padding;						/* 1	126 */
	gchar track;						/* 1	127	*/
	gchar genre;						/* 1	128 */
};

/* for testing */
void id3v1_assert (Id3v1 *tag)
{
	g_assert ((tag->title - tag->tag) == 3);
	g_assert ((tag->artist - tag->title) == 30);
	g_assert ((tag->album - tag->artist) == 30);
	g_assert ((tag->year - tag->album) == 30);
	g_assert ((tag->comment - tag->year) == 4);
	g_assert ((&(tag->padding) - tag->comment) == 28);
	g_assert ((&(tag->track) - &(tag->padding)) == 1);
	g_assert ((&(tag->genre) - &(tag->track)) == 1);
}

/* mem */
Id3v1 *id3v1_new (void)
{
	Id3v1 *tag;
	tag =  g_new0 (Id3v1, 1);

	id3v1_assert (tag);
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

	file = G_fopen (path, FILE_MODE);
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

	file = G_fopen (path, FILE_MODE);
	if (file == NULL)
	{
		return FALSE;
	}
	result = id3v1_file_have_tag (file);
	Fclose (file);

	return result;
}

gboolean id3v1_read_tag_from_path (Id3v1 *tag, const gchar *path)
{
	FILE *file;
	gboolean result;
	
	file = G_fopen (path, FILE_MODE);
	if (file == NULL)
	{
		return FALSE;
	}
	result = id3v1_read_tag_from_file (tag, file);
	Fclose (file);

	return result;
}

gboolean id3v1_write_tag_to_path (const Id3v1 *tag, const gchar *path)
{
	FILE *file;
	gboolean result;

	file = G_fopen (path, FILE_MODE);
	if (file == NULL)
	{
		return FALSE;
	}
	result = id3v1_write_tag_to_file (tag, file);
	Fclose (file);

	return result;
}

gboolean Id3v1_remove_tag_from_path (const gchar *path)
{
	FILE *file;
	gboolean result;

	file = G_fopen (path, FILE_MODE);
	if (file == NULL)
	{
		return FALSE;
	}
	result = id3v1_remove_tag_from_file (file);
	Fclose (file);

	return FALSE;
}

gboolean id3v1_file_have_tag (FILE *file)
{
	gchar tmp[ID3V1_TAG_LEN + 1];
	tmp[ID3V1_TAG_LEN] = '\0';
	fpos_t file_len;

	if (Fseek (file, 0, SEEK_END) != 0)
	{
		return FALSE;
	}
	if (Fgetpos (file, &file_len) == 0)
	{
		if (file_len <= ID3V1_LEN)
		{
			return FALSE;
		}
	}
	

	if (Fseek (file, ID3V1_POS, SEEK_END) != 0)
	{
		return FALSE;
	}

	if (!Efread (tmp, 1, ID3V1_TAG_LEN, file))
	{
		return FALSE;
	}

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

	result = Efread (tag, 1, ID3V1_LEN, file);

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

	result = Efwrite (tag, 1, ID3V1_LEN, file);

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
	return g_strndup (tag->comment, ID3V1_COMMENT_LEN);
}

gchar id3v1_get_track (Id3v1 *tag)
{
	if (tag->padding == '\0')	/* id3v1.1 */
	{
		return tag->track;
	}
	else	/* id3v1.0 without track field */
	{
		return -1;
	}
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
	tag->padding = '\0';
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
	if (comment)
	{
		id3v1_set_comment (tag, comment);
	}
	if (year)
	{
		id3v1_set_year (tag, year);
	}
	if (track)
	{
		tag->padding = '\0';
		tag->track = *track;
	}
	if (genre)
	{
		tag->genre = *genre;
	}

	return tag;
}

void id3v1_dump (Id3v1 *tag, FILE *file)
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

	fprintf (file, "<ID3V1_TAG TITLE=\"%s\" ARTIST=\"%s\" ALBUM=\"%s\" YEAR=\"%s\" COMMENT=\"%s\" TRACK =\"%x\" GENRE=\"%x\">\n", title, artist, album, year, comment, track, genre);

	g_free (title);
	g_free (artist);
	g_free (album);
	g_free (year);
	g_free (comment);
}

/* for testing */
void id3v1_dump_path (Id3v1 *tag, const gchar *path)
{
	FILE *file;
	file = G_fopen (path, DUMP_MODE);
	if (file == NULL)
	{
		return;
	}
	id3v1_write_tag_to_file (tag, file);
	Fclose (file);
}
