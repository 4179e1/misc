#include <gtk/gtk.h>
#include "id3.h"
#include "id3v1.h"
#include "wrap.h"

struct _id3
{
	Id3v1 *tag1;
	/*TODO: Id3v2 */
};

Id3 *id3_new (void) 
{
	Id3 *id3;
	id3 = g_new (Id3, 1);
	
	id3->tag1 = NULL;
	/* TODO: Id3v2 */

	return id3;
}

Id3 *id3_new_with_tag (void)
{
	Id3 *id3;
	id3 = g_new (Id3, 1);

	id3->tag1 = id3v1_new ();
	/* TODO: Id3v2 */

	return id3;
}

void id3_free (Id3 *id3)
{
	if (id3->tag1)
	{
		id3v1_free (id3->tag1);
	}
	/* TODO: Id3v2 */

	g_free (id3);
}

Id3 *id3_copy (Id3 *id3)
{
	Id3 *new;
	new = id3_new ();
	if (id3->tag1)
	{
		new->tag1 = id3v1_copy (id3->tag1);
	}
	/* TODO: Id3v2 */

	return new;
}

Id3 *id3_convert (Id3 *id3, gchar *to_codeset, gchar *from_codeset, gboolean *result)
{
	Id3 *new;
	gboolean r1 = FALSE;
	/* TODO: don't init it if Id3v2 done */
	gboolean r2 = TRUE;

	new = id3_new ();
	if (id3->tag1)
	{
		new->tag1 = id3v1_convert (id3->tag1, to_codeset, from_codeset, &r1);
	}
	/* TODO: Id3v2 */

	if (result)
	{
		*result = (r1 && r2);
	}

	return new;
}

Id3 *id3_new_from_path (const gchar *path)
{
	FILE *file;
	Id3 *id3;

	file = G_fopen (path, FILE_MODE);
	if (file == NULL)
	{
		return NULL;
	}
	id3 = id3_new_from_file (file);
	Fclose (file);

	return id3;
}

Id3 *id3_new_from_file (FILE *file)
{
	Id3 *id3;

	id3 = id3_new();
	id3->tag1 = id3v1_new_from_file (file);
	/* TODO: Id3v2 */

	return id3;
}

void id3_read_tag_from_path (Id3 *id3, const gchar *path)
{
	FILE *file;

	file = G_fopen (path, FILE_MODE);
	if (file == NULL)
	{
		return;
	}
	id3_read_tag_from_file (id3, file);
	Fclose (file);
}

void id3_write_tag_to_path (Id3 *id3, const gchar *path)
{
	FILE *file;

	file = G_fopen (path, FILE_MODE);
	if (file == NULL)
	{
		return;
	}
	id3_write_tag_to_file (id3, file);
	Fclose (file);
}

void id3_remove_tag_from_path (const gchar *path)
{
	FILE *file;

	file = G_fopen (path, FILE_MODE);
	if (file == NULL)
	{
		return;
	}
	id3_remove_tag_from_file (file);
	Fclose (file);
}

void id3_read_tag_from_file (Id3 *id3, FILE *file)
{
	if (id3->tag1)
	{
		id3v1_read_tag_from_file (id3->tag1, file);
	}
	else
	{
		g_message ("don't have Id3v1 tag");
	}
	/* TODO: Id3v2 */
}

void id3_write_tag_to_file (Id3 *id3, FILE *file)
{
	if (id3->tag1)
	{
		id3v1_write_tag_to_file (id3->tag1, file);
	}
	/* TODO: Id3v2 */
}

void id3_remove_tag_from_file (FILE *file)
{

	id3v1_remove_tag_from_file (file);
	/* TODO: Id3v2 */
}

Id3v1 *id3_get_id3v1 (Id3 *id3)
{
	return id3->tag1;
}

void id3_set_id3v1 (Id3 *id3, Id3v1 *tag1)
{
	/* FIXME: do we need to free this? */
	if (id3->tag1)
	{
		g_message ("freed previous object, set a new one");
		id3v1_free (id3->tag1);
	}
	id3->tag1 = tag1;
}

void id3_dump (Id3 *id3, FILE *file)
{
	fprintf (file, "<ID3_TAG>\n");
	if (id3->tag1)
	{
		id3v1_dump (id3->tag1, file);
	}
	/* TODO: Id3v2 */
	fprintf (file, "</ID3_TAG>\n");
}

Id3 *id3_multi_convert (Id3 *id3, gchar *to_codeset, gchar *from_codeset, gboolean *result)
{
	Id3 *new;
	gboolean r1 = FALSE;
	/* TODO: don't init it if Id3v2 done */
	gboolean r2 = TRUE;

	new = id3_new ();
	if (id3->tag1)
	{
		g_message ("%s", __func__);
		new->tag1 = (Id3v1 *)id3v1_multi_convert ((Id3v1Multi *)id3->tag1, to_codeset, from_codeset, &r1);
	}
	/* TODO: Id3v2 */

	if (result)
	{
		*result = (r1 && r2);
	}
	
	g_message ("%s do we reached here?", __func__);
	return new;
}

void id3_multi_dump (Id3 *id3, FILE *file)
{
	fprintf (file, "<ID3_MULTI_TAG>\n");
	if (id3->tag1)
	{
		id3v1_multi_dump ((Id3v1Multi *)id3->tag1, file);
	}
	/* TODO: Id3v2 */
	fprintf (file, "</ID3_MULTI_TAG>\n");
}
