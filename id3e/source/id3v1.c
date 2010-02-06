#include <gtk/gtk.h>
#include <string.h>
#include "id3v1.h"
#include "wrap.h"

#define ID3V1_LEN 128
#define ID3V1_POS (-ID3V1_LEN)

#define CONVERT_FAIL(X) (g_message ("converting \"%s\" from \"%s\" to \"%s\" failed", X, from_codeset, to_codeset))

#define CONVERT(X) (g_message ("converted \"%s\" from \"%s\" to \"%s\" ", X, from_codeset, to_codeset))

struct _id3v1
{										/* Size Total */
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

/* Bitmap for Id3v1Multi */
/* This enum can be present in a bitmap of gchar */
enum {
	ID3V1_TITLE = 0,
	ID3V1_ARTIST,		/* 1 */
	ID3V1_ALBUM,		/* 2 */
	ID3V1_YEAR,		/* 3 */
	ID3V1_COMMENT,	/* 4 */
	ID3V1_TRACK,		/* 5 */
	ID3V1_GENRE,		/* 6 */
};

/* It doesn't looks very well */
#define ID3V1_MULTI_TITLE		(1 << ID3V1_TITLE)
#define ID3V1_MULTI_ARTIST		(1 << ID3V1_ARTIST)
#define ID3V1_MULTI_ALBUM		(1 << ID3V1_ALBUM)
#define ID3V1_MULTI_YEAR 		(1 << ID3V1_YEAR)
#define ID3V1_MULTI_COMMENT		(1 << ID3V1_COMMENT)
#define ID3V1_MULTI_TRACK		(1 << ID3V1_TRACK)
#define ID3V1_MULTI_GENRE		(1 << ID3V1_GENRE)


#define ID3V1_MULTI_TITLE_IS_SAME(X) 	(((X) & ID3V1_MULTI_TITLE) == ID3V1_MULTI_TITLE)	
#define ID3V1_MULTI_ARTIST_IS_SAME(X)	(((X) & ID3V1_MULTI_ARTIST) == ID3V1_MULTI_ARTIST)
#define ID3V1_MULTI_ALBUM_IS_SAME(X)	(((X) & ID3V1_MULTI_ALBUM) == ID3V1_MULTI_ALBUM)	
#define ID3V1_MULTI_YEAR_IS_SAME(X)		(((X) & ID3V1_MULTI_YEAR) == ID3V1_MULTI_YEAR)
#define ID3V1_MULTI_COMMENT_IS_SAME(X)	(((X) & ID3V1_MULTI_COMMENT) == ID3V1_MULTI_COMMENT)	
#define ID3V1_MULTI_TRACK_IS_SAME(X)	(((X) & ID3V1_MULTI_TRACK) == ID3V1_MULTI_TRACK)	
#define ID3V1_MULTI_GENRE_IS_SAME(X)	(((X) & ID3V1_MULTI_GENRE) == ID3V1_MULTI_GENRE)	

#define ID3V1_MULTI_TITLE_SET_SAME(X)	((X) |= ID3V1_MULTI_TITLE)
#define ID3V1_MULTI_ARTIST_SET_SAME(X)	((X) |= ID3V1_MULTI_ARTIST)
#define ID3V1_MULTI_ALBUM_SET_SAME(X)	((X) |= ID3V1_MULTI_ALBUM)
#define ID3V1_MULTI_YEAR_SET_SAME(X)	((X) |= ID3V1_MULTI_YEAR)
#define ID3V1_MULTI_COMMENT_SET_SAME(X)	((X) |= ID3V1_MULTI_COMMENT)
#define ID3V1_MULTI_TRACK_SET_SAME(X)	((X) |= ID3V1_MULTI_TRACK)
#define ID3V1_MULTI_GENRE_SET_SAME(X)	((X) |= ID3V1_MULTI_GENRE)

#define ID3V1_MULTI_TITLE_SET_UNSAME(X)		((X) &= (~ID3V1_MULTI_TITLE))
#define ID3V1_MULTI_ARTIST_SET_UNSAME(X)	((X) &= (~ID3V1_MULTI_ARTIST))
#define ID3V1_MULTI_ALBUM_SET_UNSAME(X)		((X) &= (~ID3V1_MULTI_ALBUM))
#define ID3V1_MULTI_YEAR_SET_UNSAME(X)		((X) &= (~ID3V1_MULTI_YEAR))
#define ID3V1_MULTI_COMMENT_SET_UNSAME(X)	((X) &= (~ID3V1_MULTI_COMMENT))
#define ID3V1_MULTI_TRACK_SET_UNSAME(X)		((X) &= (~ID3V1_MULTI_TRACK))
#define ID3V1_MULTI_GENRE_SET_UNSAME(X)		((X) &= (~ID3V1_MULTI_GENRE))

/* 
   Currently not using the higest bit
   So the bitmap is (0111 1111), that is 0x7F
 */
#define ID3V1_MULTI_ALL					0x7F
#define ID3V1_MULTI_ALL_SET_SAME(X)		((X) = ID3V1_MULTI_ALL)
#define ID3V1_MULTI_ALL_SET_UNSAME(X)	((X) = 0x00)

/* mem */
Id3v1 *id3v1_new (void)
{
	Id3v1 *tag;

	tag =  g_new0 (Id3v1, 1);
	strncpy (tag->tag, "TAG", ID3V1_TAG_LEN);

	id3v1_assert (tag);
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
	gboolean rt = TRUE;

	g_assert (tag != NULL);

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
		/* if fail, stop, don't need to covert other string? */
		CONVERT_FAIL (title);
		rt = FALSE;
	}

	read = written = ID3V1_ARTIST_LEN;
	if ((artist_new = G_convert (artist, ID3V1_ARTIST_LEN, to_codeset, from_codeset, &read, &written)) != NULL)
	{
		id3v1_set_artist (new, artist_new);
		g_free (artist_new);
	}
	else
	{
		CONVERT_FAIL (artist);
		rt = FALSE;
	}

	read = written = ID3V1_ALBUM_LEN;
	if ((album_new = G_convert (album, ID3V1_ALBUM_LEN, to_codeset, from_codeset, &read, &written)) != NULL)
	{
		id3v1_set_album (new, album_new);
		g_free (album_new);
	}
	else
	{
		CONVERT_FAIL (album);
		rt = FALSE;
	}

	read = written = ID3V1_ALBUM_LEN;
	if ((comment_new = G_convert (comment, ID3V1_COMMENT_LEN, to_codeset, from_codeset, &read, &written)) != NULL)
	{
		id3v1_set_comment (new, comment_new);
		g_free (comment_new);
	}
	else
	{
		CONVERT_FAIL (comment);
		rt = FALSE;
	}

	if (result)
	{
		*result = rt;
	}

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

	if ((tag = id3v1_new_from_file (file)) != NULL)
	{
		tag_new = id3v1_convert (tag, to_codeset, from_codeset, result);
		id3v1_write_tag_to_file (tag_new, file);
		id3v1_free (tag);
		id3v1_free (tag_new);
	}
	else
	{
		return FALSE;
	}

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
	//tag->padding = '\0';
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
	g_assert (sizeof (Id3v1) == 128);
	g_assert ((tag->title - tag->tag) == 3);
	g_assert ((tag->artist - tag->title) == 30);
	g_assert ((tag->album - tag->artist) == 30);
	g_assert ((tag->year - tag->album) == 30);
	g_assert ((tag->comment - tag->year) == 4);
	g_assert ((&(tag->padding) - tag->comment) == 28);
	g_assert ((&(tag->track) - &(tag->padding)) == 1);
	g_assert ((&(tag->genre) - &(tag->track)) == 1);
}

/**********************************************
 * Id3v1Multi
 *********************************************/

Id3v1Multi *id3v1_multi_new (void)
{
	Id3v1Multi *mul;

	mul = g_new0 (Id3v1Multi, 1);
	ID3V1_MULTI_ALL_SET_SAME (mul->padding);

	return mul;
}

void id3v1_multi_free (Id3v1Multi *mul)
{
	g_free (mul);
}

Id3v1Multi *id3v1_multi_new_from_v1 (Id3v1 *tag)
{
	Id3v1Multi *mul;
	g_assert (tag != NULL);

	mul = g_new0(Id3v1Multi, 1);
	id3v1_multi_copy_from_v1 (mul, tag);

	return mul;
}

Id3v1Multi *id3v1_multi_copy_from_v1 (Id3v1Multi *mul, Id3v1 *tag)
{
	g_assert (mul != NULL);
	g_assert (tag != NULL);
	
	memcpy (mul, tag, ID3V1_LEN);

#if 0
	/* clear title field */
	id3v1_set_title ((Id3v1 *)mul, NULL);
#endif
	ID3V1_MULTI_ALL_SET_SAME (mul->padding);

	return mul;
}

void id3v1_multi_write_to_v1 (Id3v1Multi *mul, Id3v1 *tag)
{
	g_assert (mul != NULL);
	g_assert (tag != NULL);

	gchar *title;
	gchar *artist;
	gchar *album;
	gchar *year;
	gchar *comment;
	/* take care this */
	gchar track_val;
	gchar *track = &track_val;
	gchar genre_val;
	gchar *genre = &genre_val;
	id3v1_multi_get_content_to_param (mul, &title, &artist, &album, &year, &comment, &track, &genre);
	if (title)
	{
		id3v1_set_title (tag, title);
		g_free (title);
	}
	if (artist)
	{
		id3v1_set_artist (tag, artist);
		g_free (artist);
	}
	if (album)
	{
		id3v1_set_album (tag, album);
		g_free (album);
	}
	if (year)
	{
		id3v1_set_year (tag, year);
		g_free (year);
	}
	if (comment)
	{
		id3v1_set_comment (tag, comment);
		g_free (comment);
	}
	if (track)
	{
		id3v1_set_track (tag, *track);
		/* don't free */
	}
	if (genre)
	{
		id3v1_set_genre (tag, *genre);
		/* take care this, don't free */
	}
}

Id3v1Multi *id3v1_multi_convert (Id3v1Multi *mul, const gchar *to_codeset, const gchar *from_codeset, gboolean *result)
{	
	g_assert (mul != NULL);

	Id3v1Multi *new;
	gchar *title = NULL;
	gchar *artist = NULL;
	gchar *album = NULL;
	gchar *comment = NULL;
	gchar *title_new;
	gchar *artist_new;
	gchar *album_new;
	gchar *comment_new;
	gsize read;
	gsize write;
	gboolean rt = TRUE;

	new = id3v1_multi_new ();
	memcpy (new, mul, ID3V1_LEN);

	if (id3v1_multi_no_same (mul))
	{
		return new;
	}

	if ((to_codeset == NULL) || (from_codeset == NULL))
	{
		if (result)
		{
			*result = FALSE;
		}
		return new;
	}

	id3v1_multi_get_content_to_param (mul, &title, &artist, &album, NULL, &comment, NULL, NULL);

	if (title)
	{
		read = write = ID3V1_TITLE_LEN;
		if ((title_new = G_convert (title, ID3V1_TITLE_LEN, to_codeset, from_codeset, &read, &write)) != NULL)
		{
			id3v1_multi_set_title (new, title_new);
			g_free (title_new);
		}
		else
		{
			CONVERT_FAIL (title);
			rt = FALSE;
		}
		g_free (title);
	}
	if (artist)
	{
		read = write = ID3V1_ARTIST_LEN;
		if ((artist_new = G_convert (artist, ID3V1_ARTIST_LEN, to_codeset, from_codeset, &read, &write)) != NULL)
		{
			id3v1_multi_set_artist (new, artist_new);
			g_free (artist_new);
		}
		else
		{
			CONVERT_FAIL (artist);
			rt = FALSE;
		}
		g_free (artist);
	}
	if (album)
	{
		read = write = ID3V1_ALBUM_LEN;
		if ((album_new = G_convert (album, ID3V1_ALBUM_LEN, to_codeset, from_codeset, &read, &write)) != NULL)
		{
			id3v1_multi_set_album (new, album_new);
			g_free (album_new);
		}
		else
		{
			CONVERT_FAIL (album);
			rt = FALSE;
		}
		g_free (album);
	}
	if (comment)
	{
		read = write = ID3V1_COMMENT_LEN;
		if ((comment_new = G_convert (comment, ID3V1_COMMENT_LEN, to_codeset, from_codeset, &read, &write)) != NULL)
		{
			id3v1_multi_set_comment (new, comment_new);
			g_free (comment_new);
		}
		else
		{
			CONVERT_FAIL (comment);
			rt = FALSE;
		}
		g_free (comment);
	}

	if (result)
	{
		*result = rt;
	}

	return new;
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
	Id3v1 *tag;

	if (id3v1_multi_no_same (mul))
	{
		return TRUE;
	}

	/* read tag from file */
	tag = id3v1_new_from_file (file);
	if (tag == NULL)
	{
		/* if tag don't exist, create a new empty one */
		tag = id3v1_new ();
	}
	id3v1_multi_write_to_v1 (mul, tag);
	id3v1_write_tag_to_file (tag, file);
	id3v1_free (tag);

	return FALSE;
}

void id3v1_multi_set_from_path (Id3v1Multi *mul, const gchar *path)
{
	FILE *file;

	file = G_fopen (path, FILE_MODE);
	if (file == NULL)
	{
		return;
	}

	id3v1_multi_set_from_file (mul, file);
	Fclose (file);
}

void id3v1_multi_set_from_file (Id3v1Multi *mul, FILE *file)
{
	Id3v1Multi *cmp_tag;
	if ((cmp_tag = (Id3v1Multi *)id3v1_new_from_file (file)) == NULL)
	{
		/* the multi is not null, but the next one is null, nothing same, clear multi */
		id3v1_multi_set_content_from_param (mul, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
		return;
	}

	if (ID3V1_MULTI_TITLE_IS_SAME (mul->padding))
	{
		if (memcmp (mul->title, cmp_tag->title, ID3V1_TITLE_LEN) != 0)
		{
			id3v1_multi_set_title (mul, NULL);
		}
	}
	if (ID3V1_MULTI_ARTIST_IS_SAME (mul->padding))
	{
		if (memcmp (mul->artist, cmp_tag->artist, ID3V1_ARTIST_LEN) != 0)	/* this field not same, clear it */
		{
			id3v1_multi_set_artist (mul, NULL);
		}
	}

	if (ID3V1_MULTI_ALBUM_IS_SAME (mul->padding))
	{
		if (memcmp (mul->album, cmp_tag->album, ID3V1_ALBUM_LEN) != 0)
		{
			id3v1_multi_set_album (mul, NULL);
		}
	}

	if (ID3V1_MULTI_YEAR_IS_SAME (mul->padding))
	{
		if (memcmp (mul->year, cmp_tag->year, ID3V1_YEAR_LEN) != 0)
		{
			id3v1_multi_set_year (mul, NULL);
		}
	}

	if (ID3V1_MULTI_COMMENT_IS_SAME (mul->padding))
	{
		if (memcmp (mul->comment, cmp_tag->comment, ID3V1_COMMENT_LEN) != 0)
		{
			id3v1_multi_set_comment (mul, NULL);
		}
	}

	if (ID3V1_MULTI_TRACK_IS_SAME (mul->padding))
	{
		if ((mul->track) != (cmp_tag->track))
		{
			id3v1_multi_set_track (mul, NULL);
		}
	}

	if (ID3V1_MULTI_GENRE_IS_SAME (mul->padding))
	{
		if ((mul->genre) != (cmp_tag->genre))
		{
			id3v1_multi_set_genre (mul, NULL);
		}
	}

	id3v1_free ((Id3v1*)cmp_tag);
	return;
}

void id3v1_multi_set_title (Id3v1Multi *mul, const gchar *title)
{
	g_assert (mul != NULL);
	if (title)
	{
		id3v1_set_title ((Id3v1 *)mul, title);
		ID3V1_MULTI_TITLE_SET_SAME (mul->padding);
	}
	else
	{
		ID3V1_MULTI_TITLE_SET_UNSAME (mul->padding);
	}
}

void id3v1_multi_set_artist (Id3v1Multi *mul, const gchar *artist)
{
	g_assert (mul != NULL);

	if (artist)
	{
		id3v1_set_artist ((Id3v1 *)mul, artist);
		ID3V1_MULTI_ARTIST_SET_SAME (mul->padding);
	}
	else
	{
		ID3V1_MULTI_ARTIST_SET_UNSAME (mul->padding);
	}
}

void id3v1_multi_set_album (Id3v1Multi *mul, const gchar *album)
{
	if (album)
	{
		id3v1_set_album ((Id3v1 *)mul, album);
		ID3V1_MULTI_ALBUM_SET_SAME (mul->padding);
	}
	else
	{
		ID3V1_MULTI_ALBUM_SET_UNSAME (mul->padding);
	}
}

void id3v1_multi_set_year (Id3v1Multi *mul, const gchar *year)
{
	if (year)
	{
		id3v1_set_year ((Id3v1 *)mul, year);
		ID3V1_MULTI_YEAR_SET_SAME (mul->padding);
	}
	else
	{
		ID3V1_MULTI_YEAR_SET_UNSAME (mul->padding);
	}
}

void id3v1_multi_set_comment (Id3v1Multi *mul, const gchar *comment)
{
	if (comment)
	{
		id3v1_set_comment ((Id3v1 *)mul, comment);
		ID3V1_MULTI_COMMENT_SET_SAME (mul->padding);
	}
	else
	{
		ID3V1_MULTI_COMMENT_SET_UNSAME (mul->padding);
	}
}

void id3v1_multi_set_track (Id3v1Multi *mul, const gchar *track)
{
	if (track)
	{
		mul->track = *track;
		ID3V1_MULTI_TRACK_SET_SAME (mul->padding);
	}
	else
	{
		ID3V1_MULTI_TRACK_SET_UNSAME (mul->padding);
	}
}

void id3v1_multi_set_genre (Id3v1Multi *mul, const gchar *genre)
{
	if (genre)
	{
		mul->genre = *genre;
		ID3V1_MULTI_GENRE_SET_SAME (mul->padding);
	}
	else
	{
		ID3V1_MULTI_GENRE_SET_UNSAME (mul->padding);
	}
}

void id3v1_multi_get_content_to_param (Id3v1Multi *mul, gchar **title, gchar **artist,
		gchar **album, gchar **year, gchar **comment, gchar **track, gchar **genre)
{
	g_assert (mul != NULL);
	if (title)
	{
		if (ID3V1_MULTI_TITLE_IS_SAME (mul->padding))
		{
			*title = g_strndup (mul->title, ID3V1_TITLE_LEN);
		}
		else
		{
			*title = NULL;
		}
	}
	if (artist)
	{
		if (ID3V1_MULTI_ARTIST_IS_SAME (mul->padding))
		{
			*artist = g_strndup (mul->artist, ID3V1_ARTIST_LEN);
		}
		else
		{
			*artist = NULL;
		}
	}
	if (album)
	{
		if (ID3V1_MULTI_ALBUM_IS_SAME (mul->padding))
		{
			*album = g_strndup (mul->album, ID3V1_ALBUM_LEN);
		}
		else
		{
			*album = NULL;
		}
	}
	if (year)
	{
		if (ID3V1_MULTI_YEAR_IS_SAME (mul->padding))
		{
			*year = g_strndup (mul->year, ID3V1_YEAR_LEN);
		}
		else
		{
			*year = NULL;
		}
	}
	if (comment)
	{
		if (ID3V1_MULTI_COMMENT_IS_SAME (mul->padding))
		{
			*comment = g_strndup (mul->comment, ID3V1_COMMENT_LEN);
		}
		else
		{
			*comment = NULL;
		}
	}
	if (track)
	{
		if (ID3V1_MULTI_TRACK_IS_SAME (mul->padding))
		{
			**track = mul->track;
		}
		else
		{
			*track = NULL;
		}
	}
	if (genre)
	{
		if (ID3V1_MULTI_GENRE_IS_SAME (mul->padding))
		{
			**genre = mul->genre;
		}
		else
		{
			*genre = NULL;
		}
	}
}

void id3v1_multi_set_content_from_param (Id3v1Multi *mul, const gchar *title, const gchar *artist,
		const gchar *album, const gchar *year, const gchar *comment, const gchar *track, const gchar *genre)
{
	g_assert (mul != NULL);
	id3v1_multi_set_title (mul, title);
	id3v1_multi_set_artist (mul, artist);
	id3v1_multi_set_album (mul, album);
	id3v1_multi_set_year (mul, year);
	id3v1_multi_set_comment (mul, comment);
	id3v1_multi_set_track (mul, track);
	id3v1_multi_set_genre (mul, genre);
}

gboolean id3v1_multi_no_same (Id3v1Multi *mul)
{
	return (mul->padding == 0);
}

void id3v1_multi_dump (Id3v1Multi *mul, FILE *file)
{
	gchar *title;
	gchar *artist;
	gchar *album;
	gchar *year;
	gchar *comment;
	/* take care this!! */
	gchar track_val;
	gchar *track = &track_val;
	gchar genre_val;
	gchar *genre = &genre_val;

	id3v1_multi_get_content_to_param (mul, &title, &artist, &album, &year, &comment, &track, &genre);

	fprintf (file, "<ID3V1_MULTI");

	if (title)
	{
		fprintf (file, " TITLE=\"%s\"", title);
		g_free (title);
	}
	if (artist)
	{
		fprintf (file, " ARTIST=\"%s\"", artist);
		g_free (artist);
	}
	if (album)
	{
		fprintf (file, " ALBUM=\"%s\"", album);
		g_free (album);
	}
	if (year)
	{
		fprintf (file, " YEAR=\"%s\"", year);
		g_free (year);
	}
	if (comment)
	{
		fprintf (file, " COMMENT=\"%s\"", comment);
		g_free (comment);
	}
	if (track)
	{
		fprintf (file, " TRACK=\"%d\"", *track);
		/* don't free */
	}
	if (genre)
	{
		fprintf (file, " GENRE=\"%d\"", *genre);
		/* don't free */
	}

	fprintf (file, ">\n");
}
