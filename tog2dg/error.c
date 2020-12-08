#include <glib.h>

/* error domain */
#define PKG_DOSOMETHING_ERROR (pkg_dosomething_error_quark())

GQuark pkg_dosomething_error_quark ()
{
	static GQuark q = 0;
	if (q == 0)
	{
		q = g_quark_from_static_string ("pkg-mod-error");
	}
	return q;
}

/* error code */
enum _PKG_DOSOMETHING_ERROR
{
	PKG_DOSOMETHING_ERROR_PANIC = 0,
	PKG_DOSOMETHING_ERROR_NO_INPUT,
	PKG_DOSOMETHING_ERROR_INPUT_TOO_BORING,
	PKG_DOSOMETHING_ERROR_FAILED,
};

void pkg_dosomething_simple (GError **error)
{
	gboolean it_works = FALSE;

	if (!it_works)
	{
		g_set_error (error, PKG_DOSOMETHING_ERROR, PKG_DOSOMETHING_ERROR_PANIC, "Panic in pkg_dosomething_simple()");
	}
}

void pkg_dosomething_nested (GError **error)
{
	gboolean it_works = FALSE;
	GError *simple_error = NULL;

	if (!it_works)
	{
		g_set_error (error, PKG_DOSOMETHING_ERROR, PKG_DOSOMETHING_ERROR_PANIC, "Panic in pkg_dosomething_nested()");
		return;
	}

	pkg_dosomething_simple (&simple_error);
	if (simple_error !=	NULL)
	{
		g_propagate_error (error, simple_error);
	}
}

int main (void)
{
	GError *error = NULL;
	pkg_dosomething_nested (&error);
	if (error != NULL)
	{
		g_message (error->message);
		g_error_free (error);
	}

	return 0;
}
