#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
	int i;
	int len;
	size_t copy;
	FILE *in;
	FILE *out;
	char name[1024];
	char buf[4096];

	for (i = 1; i < argc; i++)
	{
		len = strlen (argv[i]);
		if ((len > 4) && (strcasecmp (argv[i] + len -4, ".jpg") == 0))
		{
			in = fopen (argv[i], "rb");
			if (in == NULL)
			{
				fprintf (stderr, "Can not open %s\n", argv[i]);
				continue;
			}

			snprintf (name, len - 4 + 1, "%s", argv[i]);
			strncat (name, "-copy.jpg", sizeof (name));

			out = fopen (name, "wb+");
			if (out == NULL)
			{
				fprintf (stderr, "Can not copy file %s\n", name);
				fclose (in);
				continue;
			}

			while (feof (in) == 0)
			{
				copy = fread (buf, 1, sizeof (buf), in);
				fwrite (buf, 1, copy, out);
			}

			fclose (in);
			fclose (out);
		}
	}

	return 0;
}
