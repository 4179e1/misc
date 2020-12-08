#include <stdio.h>
#define ID3V1_TAG "TAG"
#define ID3V1_TAG_LEN 3
#define ID3V1_TITLE_LEN 30
#define ID3V1_ARTIST_LEN 30
#define ID3V1_ALBUM_LEN 30
#define ID3V1_YEAR_LEN 4
#define ID3V1_COMMENT_LEN 28
#define ID3V1_TRACK_LEN 1
#define ID3V1_GENRE_LEN 1
struct _id3v1
{
	char tag[ID3V1_TAG_LEN];
	char title[ID3V1_TITLE_LEN];
	char artist[ID3V1_ARTIST_LEN];
	char album[ID3V1_ALBUM_LEN];
	char year[ID3V1_YEAR_LEN];
	char comment[ID3V1_COMMENT_LEN];
	char padding;
	char track;
	char genre;
};

int main (void)
{
	struct _id3v1 i;

	printf ("sizeof struct: %d\n", sizeof(i));
	printf ("%p\n", i.tag);
	printf ("%p\n", i.title);
	printf ("%p\n", i.artist);
	printf ("%p\n", i.album);
	printf ("%p\n", i.year);
	printf ("%p\n", i.comment);
	printf ("%p\n", &(i.padding));
	printf ("%p\n", &(i.track));
	printf ("%p\n", &(i.genre));

	return 0;
}
