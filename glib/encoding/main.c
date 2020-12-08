#include <glib.h>
#include <glib/gstdio.h>
#include <stdio.h>

int main (void)
{
	FILE *fin;
	FILE *fout;
	gchar *src;
	gchar *dest;
	gsize src_len;
	gsize dest_len;
	GError *error = NULL;

	fin = g_fopen ("abc.txt", "rb+");
	fout = g_fopen ("def.txt", "wb");
	src = g_new0 (gchar, 1024);

	src_len = fread (src, 1, 1024, fin);

	dest = g_convert (src, src_len, "UTF-8", "GBK", &src_len, &dest_len, &error);
	if (error != NULL)
	{
		g_message ("%s", error->message);
		return -1;
	}

	g_print ("read %u bytes, wrote %u bytes\n", src_len, dest_len);
	
	fwrite (dest, dest_len, 1, fout);

	fclose (fin);
	fclose (fout);

	return 0;
}
