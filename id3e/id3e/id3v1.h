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
#define ID3V1_YEAR_LEN 4
#define ID3V1_COMMENT_LEN 28
#define ID3V1_TRACK_LEN 1
#define ID3V1_GENRE_LEN 1

Id3v1 *id3v1_new (void);
void id3v1_free (Id3v1 *tag);

Id3v1 *id3v1_copy (Id3v1 *tag);
Id3v1 *id3v1_convert (Id3v1 *tag, gchar *to_codeset, gchar *from_codeset, gboolean *result);

/* return NULL if fail */
Id3v1 *id3v1_new_from_path (const gchar *path);
Id3v1 *id3v1_new_from_file (FILE *file);

gboolean id3v1_path_have_tag (const gchar *path);
gboolean id3v1_read_tag_from_path (Id3v1 *tag, const gchar *path);
gboolean id3v1_write_tag_to_path (const Id3v1 *tag, const gchar *path);
gboolean Id3v1_remove_tag_from_path (const gchar *path);

gboolean id3v1_file_have_tag (FILE *file);
gboolean id3v1_read_tag_from_file (Id3v1 *tag, FILE *file);
gboolean id3v1_write_tag_to_file (const Id3v1 *tag, FILE *file);
gboolean id3v1_remove_tag_from_file (FILE *file);

/* these return values need to be free */
gchar *id3v1_get_title (Id3v1 *tag);
gchar *id3v1_get_artist (Id3v1 *tag);
gchar *id3v1_get_album (Id3v1 *tag);
gchar *id3v1_get_year (Id3v1 *tag);
gchar *id3v1_get_comment (Id3v1 *tag);

gchar id3v1_get_track (Id3v1 *tag);
gchar id3v1_get_genre (Id3v1 *tag);


/**
 * set property, if pointer to new property is NULL, 
 * it will clear the previous property with 0
 */
void id3v1_set_title (Id3v1 *tag, gchar *title);
void id3v1_set_artist (Id3v1 *tag, gchar *artist);
void id3v1_set_album (Id3v1 *tag, gchar *album);
void id3v1_set_year (Id3v1 *tag, gchar *year);
void id3v1_set_comment (Id3v1 *tag, gchar *comment);

void id3v1_set_track (Id3v1 *tag, gchar track);
void id3v1_set_genre (Id3v1 *tag, gchar genre);

/* FIXME: a bit complex, we really need this func? */
/* "const gchar **p": p is a pointer to (a pointer to const gchar)  */
Id3v1 *id3v1_get_content_to_param (Id3v1 *tag, gchar**title, 
		gchar **artist, gchar **album,gchar **year, 
		gchar **comment, gchar *track, gchar *genre);

/* ingnore if property pointer is NULL */
Id3v1 *id3v1_set_content_from_param (Id3v1 *tag,
		gchar *title, gchar *artist, gchar *album,
		gchar *year, gchar *comment, gchar *track, gchar *genre);		

void id3v1_dump (Id3v1 *tag, FILE *file);
/* 
  the difference between id3v1_dump_path & id3v1_write_tag_to_path is
  the open file mode, id3v1_dump_path will create a new file if it doesn't 
  exist. there is no id3v1_dump_file(), id3v1_write_tag_to_file will work
 */
void id3v1_dump_path (Id3v1 *tag, const gchar *path);
void id3v1_assert (Id3v1 *tag);
#endif /* _ID3V1_H */
