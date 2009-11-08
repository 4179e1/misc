#include <gtk/gtk.h>
#include "id3v1.h"

struct _id3v1
{
	gchar tag[ID3V1_TAG_LEN];
	gchar title[ID3V1_TITLE_LEN];
	gchar artist[ID3V1_ARTIST_LEN];
	gchar album[ID3V1_ALBUM_LEN];
	gchar year[ID3V1_YEAR_LEN];
	gchar comment[ID3V1_COMMENT_LEN];
	ghcar comment;
	gchar gener;
}

Id3v1 *id3v1_new (void)
{
	return g_new (sturct _id3v1);
}

void id3v1_free (Id3v1 *id3v1)
{
	g_free (id3v1);
}
