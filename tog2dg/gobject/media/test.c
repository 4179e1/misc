#include <stdio.h>
#include "media.h"
#include "cd.h"

void reference (void)
{
	Media *m1;
	Media *m2;
	Media *weak;

	m1 = g_object_new (TYPE_MEDIA, NULL);

	/* set m2 to a strong reference from m1 */
	m2 = g_object_ref (m1);

	/* set weak to a weak reference from m2 */
	weak = m2;
	g_object_add_weak_pointer (G_OBJECT (m1), (gpointer) &weak);

	/* remove one strong reference */
	g_object_unref (m2);

	/* see if weak is NULL,  meaning that object is gone */
	if (weak == NULL)
	{
		g_print ("weak is NULL, object is gone\n");
	}
	else
	{
		g_print ("weak is not NULL, object is still in memory\n");
	}

	/* remove another reference */
	g_object_unref (m1);

	/* see if weak is NULL,  meaning that object is gone */
	if (weak == NULL)
	{
		g_print ("weak is NULL, object is gone\n");
	}
	else
	{
		g_print ("weak is not NULL, object is still in memory\n");
	}
}

void property (void)
{
	Media *m1;

	guint nr;
	gboolean is_unpacked;

	g_type_init();

	m1 = g_object_new (TYPE_MEDIA,
			"inventory-id", 4,
			"orig-package", FALSE,
			NULL);

	g_object_get (m1,
			"inventory-id", &nr,
			"orig-package", &is_unpacked,
			NULL);
	g_print ("inventory-id = %d, orig-package = %s\n", nr, is_unpacked ? "TRUE" : "FALSE");
	g_object_set (m1,
			"inventory-id", nr,
			"orig-package", is_unpacked,
			NULL);
	g_object_get (m1,
			"inventory-id", &nr,
			"orig-package", &is_unpacked,
			NULL);
	g_print ("inventory-id = %d, orig-package = %s\n", nr, is_unpacked ? "TRUE" : "FALSE");

	g_object_unref (m1);
}

static void meep_meep (Media *media)
{
	guint nr;
	g_object_get (media, "inventory-id", &nr, NULL);

	g_print ("Meep-meep! (Inventory number: \%d)\n", nr);
}

void zignal (void)
{
	Media *m;
	gboolean return_val = TRUE;
	gulong handler_id;

	m = g_object_new (TYPE_MEDIA,
			"inventory-id", 10,
			"orig-package", TRUE,
			NULL);

	handler_id = g_signal_connect (m, "unpacked", G_CALLBACK (meep_meep), NULL);

	g_signal_emit_by_name (m, "unpacked");

	/* remove handler */
	if (g_signal_handler_is_connected (m, handler_id))
	{
		g_print ("meepmeep is connected to media. Detaching...\n");
	}
	g_signal_handler_disconnect (m, handler_id);
	if (!g_signal_handler_is_connected (m, handler_id))
	{
		g_print ("meepmeep no longer connected:\n");
		g_signal_emit_by_name (m, "unpacked");
	}

	g_signal_emit_by_name (m, "throw-out", TRUE, &return_val);
	if (return_val)
	{
		g_print ("Signal (throw-out): returned TRUE.\n");
	}
	else
	{
		g_print ("Signal (throw-out); returned FALSE.\n");
	}

	g_signal_emit_by_name (m, "throw-out", FALSE, &return_val);
	if (return_val)
	{
		g_print ("Signal (throw-out): returned TRUE.\n");
	}
	else
	{
		g_print ("Signal (throw-out); returned FALSE.\n");
	}

	/* XXX don't do this */
	// g_signal_emit_by_name (m, "throw-out", FALSE /* , &return_val */);

	g_object_unref (m);
}

static void ding (Media *media)
{
	g_print ("Ding.\n");
}

static void dong (Media *media)
{
	g_print ("Dong.\n");
}

static gboolean my_hook (GSignalInvocationHint *ihint,
		guint n_param_values,
		const GValue *param_values,
		gpointer *data)
{
	static gint n = 0;
	guint inv_nr;
	Media *m;
	GObject *obj;

	g_print ("my_hook(): ");

	if (n_param_values > 0)
	{
		obj = g_value_get_object (param_values + 0);
		if (IS_MEDIA (obj))
		{
			m = MEDIA (obj);
			g_object_get (m, "inventory-id", &inv_nr, NULL);
			g_print ("inventory number = %d.\n", inv_nr);
		}
		else
		{
			g_print ("called with invalid object\n");
		}
	}
	else
	{
		g_print ("called with invalid parameters\n");
	}

	n++;
	g_print ("my_hook(): invocation #%d", n);

	if (n == 2)
	{
		g_print (" (last time)\n");
		return FALSE;
	}
	else
	{
		g_print ("\n");
		return TRUE;
	}
}

void zignal2 (void)
{
	Media *m;
	guint unpacked_signal_id;

	m = g_object_new (TYPE_MEDIA, "inventory-id", 5, "orig-package", TRUE,  NULL);

	unpacked_signal_id = g_signal_lookup ("unpacked", TYPE_MEDIA);
	if (unpacked_signal_id != 0)
	{
		g_signal_add_emission_hook (unpacked_signal_id, 0, (GSignalEmissionHook)my_hook, NULL, NULL);
	}
	else
	{
		g_print ("no such signal\n");
	}

	g_signal_connect (m, "unpacked", G_CALLBACK (meep_meep), NULL);
	g_signal_connect (m, "unpacked::ding", G_CALLBACK (ding), NULL);
	g_signal_connect (m, "unpacked::dong", G_CALLBACK (dong), NULL);

	g_signal_emit_by_name (m, "unpacked::ding");
	g_signal_emit_by_name (m, "unpacked::dong");
	g_signal_emit_by_name (m, "unpacked");

	g_object_unref (m);
}

void signal_list ()
{
	guint i, nr, *sigs, *ptr;

	sigs = g_signal_list_ids (TYPE_MEDIA, &nr);
	g_print ("ID\tName\n");
	g_print ("----  ----------\n");
	i = 0;

	for (ptr = sigs; i < nr; i++, ptr++)
	{
		g_print ("%-4d %s\n", *ptr, g_signal_name (*ptr));
	}
	g_print ("\nTotal signals: %d\n", nr);
	g_free (sigs);
}

void inherit (void)
{
	Media *media;
	CD *cd;
	gboolean r;

	guint nr;
	gboolean is_unpacked;

	media = g_object_new (TYPE_MEDIA, NULL);

	cd = g_object_new (TYPE_CD, "inventory-id", 423, "writable", FALSE, NULL);

	g_object_get (cd, "inventory-id", &nr, "writable", &is_unpacked, NULL);

	g_print ("cd: writable = %s, inventory-id = %d\n", is_unpacked ? "ture" : "false", nr);

	g_signal_emit_by_name (media, "unpacked", NULL);
	g_signal_emit_by_name (media, "throw-out", FALSE, &r);
	g_signal_emit_by_name (cd, "unpacked", NULL);
	g_signal_emit_by_name (cd, "throw-out", TRUE, &r);

	g_print ("cd is %sMedia object\n", IS_MEDIA(cd) ? "a " : "not a ");

	g_print ("media is %sCD object\n", IS_CD(media) ? "a " : "not a ");

	g_object_unref (cd);
	g_object_unref (media);
}

void interface (void)
{
	CD *cd;

	cd = g_object_new (TYPE_CD, NULL);

	clean (CLEANABLE (cd));

	g_object_unref (cd);
}

int main (int argc, char *argv[])
{
	g_type_init();
	
	//property ();
	//reference ();
	//zignal ();
	//zignal2 ();
	//signal_list ();
	//inherit ();
	interface ();

	return 0;
}
