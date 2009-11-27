#ifndef _ID3_H
#define _ID3_H

#include <gtk/gtk.h>
#include "id3v1.h"

typedef struct _id3 Id3;

Id3 *id3_new (void);
Id3 *id3_new_with_tag (void);
void id3_free (Id3 *id3);

Id3 *id3_copy (Id3 *id3);
Id3 *id3_convert (Id3 *id3, gchar *to_codeset, gchar *from_codeset, gboolean *result);

Id3 *id3_new_from_path (const gchar *path);
Id3 *id3_new_from_file (FILE *file);

void id3_read_tag_from_path (Id3 *id3, const gchar *path);
void id3_write_tag_to_path (Id3 *id3, const gchar *path);
void id3_remove_tag_from_path (const gchar *path);

void id3_read_tag_from_file (Id3 *id3, FILE *file);
void id3_write_tag_to_file (Id3 *id3, FILE *file);
void id3_remove_tag_from_file (FILE *file);

Id3v1 *id3_get_id3v1 (Id3 *id3);
void id3_set_id3v1 (Id3 *id3, Id3v1 *tag1);

void id3_dump (Id3 *id3, FILE *file);
void id3_multi_dump (Id3 *id3, FILE *file);
/* multi */
Id3 *id3_multi_convert (Id3 *id3, gchar *to_codeset, gchar *from_codeset, gboolean *result);
#endif /* _ID3_H */
