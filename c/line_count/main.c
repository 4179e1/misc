#include <glib.h>
#include <glib/gstdio.h>
#include <string.h>
#define MAXLINE 1024

static gint files = 0;
static gint rows = 0;

static gint get_rows (const gchar *filename)
{
	gint count = 0;
	gint c;

	FILE *fp;

	if (NULL == (fp = g_fopen(filename, "r")))
	{
		fprintf(stderr, "can't open %s\n", filename);
		return -1;
	}

	while ((c = getc (fp)) != EOF)
	{
		if ( '\n' == c )
			count++;
	}

	if (fclose (fp) != 0)
	{
		fprintf (stderr, "fclose() fail\n");
		return -1;
	}

	return count;
}

static gboolean identify (const gchar *path){
	gint len = strlen(path);

	if (len >= 2)
	{
		const gchar *ptr = (path + len - 2);
		if (strcmp (ptr, ".c") == 0 || strcmp (ptr, ".h") == 0)
		{
			return TRUE;
		}

		if (len >= 4)
		{
			ptr-=2;
			if (strcmp (ptr, ".cpp") == 0)
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}

static void listfile (gchar *path)
{
	GDir *dir;
	gchar *ptr;
	GError *error = NULL;
	const gchar *name;
	gint len;

	len = strlen (path);

	if (!g_file_test (path, G_FILE_TEST_IS_DIR))
	{
		if (identify (path))
		{
			if ((len = get_rows (path)) >= 0)
			{
				g_print ("%d\t%s\n", len, path);
				files++;
				rows += len;
			}
		}
		return;
	}

	ptr = path + len;
	*ptr++ = '/';
	*ptr = 0;

	dir = g_dir_open (path, 0, &error);
	if (error != NULL)
	{
		g_warning ("g_dir_openerror: %s\n", error->message);
		g_free (error);
		return;
	}

	while ((name = g_dir_read_name (dir)) != NULL)
	{
		strcpy (ptr, name);
		listfile (path);
	}

	ptr[-1] = 0;

	g_dir_close (dir);
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf (stderr, "usage: count <path>\n");
		return 1;
	}
	gchar *path;
	path = g_new0(gchar, MAXLINE);

	strcpy (path, argv[1]);

	listfile(path);

	g_print ("\n%d lines in %d files, average %d linse in a file\n",
			rows, files, (files == 0 ? 0 : (rows/files)));

	g_free (path);

	return 0;
}
