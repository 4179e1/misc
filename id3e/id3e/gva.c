#include <gtk/gtk.h>
#include "gva.h"
#include "gv1.h"

struct _gva
{
	Gv1 *gv1;
	/* TODO: Gv2 */
	gboolean is_sensitive;
	GvaSelection current;
};

Gva *gva_new ()
{
	Gva *gva;
	gva = g_new (Gva, 1);
	gva->is_sensitive = FALSE;
	gva->current = GVA_SELECTION_V1;
	gva->gv1 = gv1_new ();
	/* TODO: Gv2 */
	return gva;
}

void gva_free (Gva *gva)
{
	gv1_free (gva->gv1);
	/* TODO: Gv2 */
	g_free (gva);
}

Gva *gva_init (Gva *gva, GtkBuilder *builder)
{
	gv1_init (gva->gv1, builder);
	/* TODO: Gv2 */
	return gva;
}

Gva *gva_reset (Gva *gva)
{
	gv1_reset (gva->gv1);
	/* TODO: Gv2 */
	return gva;
}

Gva *gva_set_sensitive (Gva *gva, gboolean status)
{
	gv1_set_sensitive (gva->gv1, status);
	/* TODO: Gv2 */
	gva->is_sensitive = status;
	return gva;
}

gboolean gva_is_sensitive (Gva *gva)
{
	return gva->is_sensitive;
}

GvaSelection gva_get_selection (Gva *gva)
{
	return gva->current;
}

void gva_set_selection (Gva *gva, GvaSelection select)
{
	gva->current = select;
}

Id3 *gva_write_to_id3 (Gva *gva, Id3 *id3)
{
	if (gva->current == GVA_SELECTION_V1)
	{
		Id3v1 *tag1;

		tag1 = id3v1_new ();
		id3_set_id3v1 (id3, tag1);
		gv1_write_to_id3v1 (gva->gv1, tag1);
	}
	else if (gva->current == GVA_SELECTION_V2)
	{
		g_message ("nothing to do here");
		/* TODO: Gv2 */
	}
	else
	{
		g_warning ("should not reach here");
	}
	return id3;
}

Gva *gva_read_from_id3 (Gva *gva, Id3 *id3)
{
	Id3v1 *tag1;
	if ((tag1 = id3_get_id3v1 (id3)) != NULL)
	{
		gv1_read_from_id3v1 (gva->gv1, tag1);
	}
	/* TODO: Gv2 */
	return gva;
}

Id3 *gva_write_to_id3_multi (Gva *gva, Id3 *id3)
{
	if (gva->current == GVA_SELECTION_V1)
	{
		Id3v1Multi *mtag1;
		mtag1 = id3v1_multi_new ();
		id3_set_id3v1 (id3, (Id3v1 *)mtag1);
		gv1_write_to_id3v1_multi (gva->gv1, mtag1);
	}
	else if (gva->current == GVA_SELECTION_V2)
	{
		g_message ("nothint to do here");
		/* TODO: Gv2 */
	}
	else
	{
		g_warning ("should not reach here");
	}
	return id3;
}

Gva *gva_read_from_id3_multi (Gva *gva, Id3 *id3)
{
	Id3v1Multi *mtag1;
	if ((mtag1= (Id3v1Multi *)id3_get_id3v1 (id3)) != NULL)
	{
		gv1_read_from_id3v1_multi (gva->gv1, mtag1);
	}
	/* TODO: Gv2 */
	return gva;
}
