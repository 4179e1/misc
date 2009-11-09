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
	gchar padding;
	gchar track;
	gchar gener;
};

Id3v1 *id3v1_new (void)
{
	Id3v1 *tag;
	tag =  g_new0 (Id3v1, 1);
	snprintf (tag->tag, ID3V1_TAG_LEN, ID3V1_TAG);
	return tag;
}

void id3v1_free (Id3v1 *id3v1)
{
	g_free (id3v1);
}
