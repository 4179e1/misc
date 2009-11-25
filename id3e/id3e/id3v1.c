#include <gtk/gtk.h>
#include <string.h>
#include "id3v1.h"
#include "wrap.h"

#define ID3V1_TAG "TAG"
#define ID3V1_TAG_LEN 3
#define ID3V1_TITLE_LEN 30
#define ID3V1_ARTIST_LEN 30
#define ID3V1_ALBUM_LEN 30
#define ID3V1_YEAR_LEN 4
#define ID3V1_COMMENT_LEN 28
#define ID3V1_TRACK_LEN 1
#define ID3V1_GENRE_LEN 1

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

struct _id3v1_multi
{
	gchar tag[ID3V1_TAG_LEN];			/* 3	3	*/
	/* while selecting one more items, we don't need title field */
	gchar artist_same;					/* 1	4	*/
	gchar album_same;					/* 1	5	*/
	gchar year_same;					/* 1	6	*/
	gchar comment_same;					/* 1	7	*/
	gchar genre_same;					/* 1	8	*/
	gchar padding2[25];					/* 25	33	*/
	gchar artist[ID3V1_ARTIST_LEN];		/* 30	63	*/
	gchar album[ID3V1_ALBUM_LEN];		/* 30	93	*/
	gchar year[ID3V1_YEAR_LEN];			/* 4	97	*/
	gchar comment[ID3V1_COMMENT_LEN];	/* 28	125	*/
	gchar padding;						/* 1	126 */
	gchar track;						/* 1	127	*/
	gchar genre;						/* 1	128 */
};

/* mem */
Id3v1 *id3v1_new (void)
{
	Id3v1 *tag;

	tag =  g_new0 (Id3v1, 1);
	strncpy (tag->tag, "TAG", ID3V1_TAG_LEN);

	return tag;
}

void id3v1_free (Id3v1 *id3v1)
{
	g_free (id3v1);
}

Id3v1 *id3v1_copy (Id3v1 *tag)
{
	Id3v1 *new;
	new = id3v1_new ();
	memcpy (new, tag, ID3V1_LEN);
	return new;
}

Id3v1 *id3v1_convert (Id3v1 *tag, const gchar *to_codeset, const gchar *from_codeset, gboolean *result)
{
	Id3v1 *new;	
	gchar *title;
	gchar *artist;
	gchar *album;
	gchar *comment;

	gchar *title_new;
	gchar *artist_new;
	gchar *album_new;
	gchar *comment_new;

	gsize read;
	gsize written;

	g_assert (tag != NULL);

	if (result)
	{
		*result = TRUE;
	}

	new = id3v1_copy (tag);

	if ((to_codeset == NULL) || (from_codeset == NULL) )
	{
		*result = FALSE;
		return new;
	}
	g_message ("converting from \"%s\" to \"%s\"", from_codeset, to_codeset);

	id3v1_get_content_to_param (tag, &title, &artist, &album, NULL, &comment, NULL, NULL);

	read = written = ID3V1_TITLE_LEN;
	if ((title_new = G_convert (title, ID3V1_TITLE_LEN, to_codeset, from_codeset, &read, &written)) != NULL)
	{
		id3v1_set_title (new, title_new);
		g_free (title_new);
	}
	else
	{
		/* if fail, stop, don't need to covert other string */
		g_message ("convert \"%s\" to %s failed", title, to_codeset);
		if (result)
		{
			*result = FALSE;
		}
	}

	read = written = ID3V1_ARTIST_LEN;
	if ((artist_new = G_convert (artist, ID3V1_ARTIST_LEN, to_codeset, from_codeset, &read, &written)) != NULL)
	{
		id3v1_set_artist (new, artist_new);
		g_free (artist_new);
	}
	else
	{
		g_message ("convert \"%s\" to %s failed", artist, to_codeset);
		if (result)
		{
			*result = FALSE;
		}
	}

	read = written = ID3V1_ALBUM_LEN;
	if ((album_new = G_convert (album, ID3V1_ALBUM_LEN, to_codeset, from_codeset, &read, &written)) != NULL)
	{
		id3v1_set_album (new, album_new);
		g_free (album_new);
	}
	else
	{
		g_message ("convert \"%s\" to %s failed", album, to_codeset);
		if (result)
		{
			*result = FALSE;
		}
	}

	read = written = ID3V1_ALBUM_LEN;
	if ((comment_new = G_convert (comment, ID3V1_COMMENT_LEN, to_codeset, from_codeset, &read, &written)) != NULL)
	{
		id3v1_set_comment (new, comment_new);
		g_free (comment_new);
	}
	else
	{
		g_message ("convert \"%s\" to %s failed", comment, to_codeset);
		if (result)
		{
			*result = FALSE;
		}
	}

/* return of function */	

	g_free (title);
	g_free (artist);
	g_free (album);
	g_free (comment);

	return new;
}

gboolean id3v1_convert_path (const gchar *path, const gchar *to_codeset, const gchar *from_codeset, gboolean *result)
{
	FILE *file;
	gboolean stat;

	file = G_fopen (path, FILE_MODE);
	if (file == NULL)
	{
		return FALSE;
	}
	stat = id3v1_convert_file (file, to_codeset, from_codeset, result);
	Fclose (file);

	return stat;
}

gboolean id3v1_convert_file (FILE *file, const gchar *to_codeset, const gchar *from_codeset, gboolean *result)
{
	Id3v1 *tag;
	Id3v1 *tag_new;

	tag = id3v1_new_from_file (file);
	tag_new = id3v1_convert (tag, to_codeset, from_codeset, result);
	id3v1_write_tag_to_file (tag_new, file);

	id3v1_free (tag);
	id3v1_free (tag_new);

	return *result;
}

Id3v1 *id3v1_new_from_path (const gchar *path)
{
	FILE *file;
	Id3v1 *tag;

	file = G_fopen (path, FILE_MODE);
	if (file == NULL)
	{
		return NULL;
	}
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
	long file_len;

	if (Fseek (file, 0, SEEK_END) != 0)
	{
		return FALSE;
	}

	if ((file_len = Ftell (file)) != -1)
	{
		if (file_len < ID3V1_LEN)
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

void id3v1_set_title (Id3v1 *tag, const gchar *title)
{
	memset (tag->title, 0, ID3V1_TITLE_LEN);
	if (title != NULL)
	{
		strncpy (tag->title, title, ID3V1_TITLE_LEN);
	}
}

void id3v1_set_artist (Id3v1 *tag, const gchar *artist)
{
	memset (tag->artist, 0, ID3V1_ARTIST_LEN);
	if (artist != NULL)
	{
		strncpy (tag->artist, artist, ID3V1_ARTIST_LEN);
	}
}

void id3v1_set_album (Id3v1 *tag,const gchar *album)
{
	memset (tag->album, 0, ID3V1_ALBUM_LEN);
	if (album != NULL)
	{
		strncpy (tag->album, album, ID3V1_ALBUM_LEN);
	}
}


void id3v1_set_year (Id3v1 *tag, const gchar *year)
{
	memset (tag->year, 0, ID3V1_YEAR_LEN);
	if (year != NULL)
	{
		strncpy (tag->year, year, ID3V1_YEAR_LEN);
	}
}


void id3v1_set_comment (Id3v1 *tag, const gchar *comment)
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
		const gchar *title, const gchar *artist, const gchar *album,
		const gchar *year, const gchar *comment,
		const gchar *track, const gchar *genre)
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

Id3v1Multi *id3v1_multi_new (void)
{
	Id3v1Multi *mul;
	mul = g_new0 (Id3v1Multi, 1);
	mul->artist_same = 1;
	mul->album_same = 1;
	mul->year_same = 1;
	mul->comment_same = 1;
	mul->genre_same = 1;
	return mul;
}
void id3v1_multi_free (Id3v1Multi *mul)
{
	g_free (mul);
}

gboolean id3v1_multi_write_to_path (Id3v1Multi *mul, const gchar *path)
{
	FILE *file;
	gboolean result;
	
	file = G_fopen (path, FILE_MODE);
	if (file == NULL)
	{
		return FALSE;
	}

	result = id3v1_multi_write_to_file (mul, file);
	Fclose (file);

	return result;
}

gboolean id3v1_multi_write_to_file (Id3v1Multi *mul, FILE *file)
{
	return FALSE;
}

void id3v1_multi_get_content_to_param (Id3v1Multi *mul, gchar **artist,
		gchar **album, gchar **year, gchar **comment, gchar *genre)
{
	g_assert (mul != NULL);
	id3v1_get_content_to_param ((Id3v1 *)mul, NULL, artist, album, year, comment, NULL, genre);
}

void id3v1_multi_set_content_from_param (Id3v1Multi *mul, const gchar *artist,
		const gchar *album, const gchar *year, const gchar *comment, const gchar *genre)
{
	g_assert (mul != NULL);
	id3v1_set_content_from_param ((Id3v1 *)mul, NULL, artist, album, year, comment, NULL, genre);
}
