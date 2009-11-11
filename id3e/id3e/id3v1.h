#ifndef _ID3V1_H
#define _ID3V1_H

#include <stdio.h>
#include <gtk/gtk.h>

/**
 * using ID3v1.1
 */
typedef struct _id3v1 Id3v1;

#define ID3V1_TAG "TAG"
#define ID3V1_TAG_LEN 3
#define ID3V1_TITLE_LEN 30
#define ID3V1_ARTIST_LEN 30
#define ID3V1_ALBUM_LEN 30
#define ID3V1_YEAR_LEN 30
#define ID3V1_COMMENT_LEN 28
#define ID3V1_TRACK_LEN 1
#define ID3V1_GENRE_LEN 1

Id3v1 *Id3v1_new (void);
void id3v1_free (Id3v1 *tag);

gboolean id3v1_path_have_tag (const gchar *path);
Id3v1 *id3v1_read_tag_from_path (const gchar *path, Id3v1 *tag);
gboolean id3v1_write_tag_to_path (const Id3v1 *tag, const gchar *path);
gboolean Id3v1_remove_tag_from_path (const gchar *path);

gboolean id3v1_file_have_tag (FILE *file);
Id3v1 *id3v1_read_tag_from_file (FILE *file, Id3v1 *tag);
gboolean id3v1_write_tag_to_file (const Id3v1 *tag, FILE *file);
gboolean id3v1_remove_tag_from_file (FILE *file);

const gchar *id3v1_get_title (Id3v1 *tag);
const gchar *id3v1_get_artist (Id3v1 *tag);
const gchar *id3v1_get_album (Id3v1 *tag);
const gchar *id3v1_get_year (Id3v1 *tag);
const gchar *id3v1_get_comment (Id3v1 *tag);
gchar id3v1_get_track (Id3v1 *tag);
gchar id3v1_get_genre (Id3v1 *tag);

/**
 * set property, and return the pointer in struct
 * if pointer to new property is NULL, 
 * it will clear the previous property with 0
 */
const gchar *id3v1_set_title (Id3v1 *tag, gchar *title);
const gchar *id3v1_set_artist (Id3v1 *tag, gchar *artist);
const gchar *id3v1_set_album (Id3v1 *tag, gchar *album);
const gchar *id3v1_set_year (Id3v1 *tag, gchar *year);
const gchar *id3v1_set_comment (Id3v1 *tag, gchar *comment);
gchar id3v1_set_track (Id3v1 *tag, gchar track);
gchar id3v1_set_genre (Id3v1 *tag, gchar genre);

/* FIXME: a bit complex, we really need this func? */
/* "const gchar **p": p is a pointer to (a pointer to const gchar)  */
Id3v1 *id3v1_get_content_to_param (Id3v1 *tag, const gchar**title, 
		const gchar **artist, const gchar **album, const gchar **year, 
		const gchar **comment, gchar *track, gchar *genre);

/* ingnore if property pointer is NULL */
Id3v1 *id3v1_set_content_from_param (Id3v1 *tag,
		gchar *title, gchar *artist, gchar *album,
		gchar *year, gchar *comment, gchar *track, gchar *genre);		
#endif /* _ID3V1_H */
