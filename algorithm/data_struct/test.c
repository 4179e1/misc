#include <stdio.h>
#include "base.h"
#include "hash.h"

char *a[] = 
{
	"AENC",
	"APIC",
	"ASPI",
	"COMM",
	"COMR",
	"ENCR",
	"EQU2",
	"ETCO",
	"GEOB",
	"GRID",
	"LINK",
	"MCDI",
	"MLLT",
	"OWNE",
	"PRIV",
	"PCNT",
	"POPM",
	"POSS",
	"RBUF",
	"RVA2",
	"RVRB",
	"SEEK",
	"SIGN",
	"SYLT",
	"SYTC",
	"TALB",
	"TBPM",
	"TCOM",
	"TCON",
	"TCOP",
	"TDEN",
	"TDLY",
	"TDOR",
	"TDRC",
	"TDRL",
	"TDTG",
	"TENC",
	"TEXT",
	"TFLT",
	"TIPL",
	"TIT1",
	"TIT2",
	"TIT3",
	"TKEY",
	"TLAN",
	"TLEN",
	"TMCL",
	"TMED",
	"TMOO",
	"TOAL",
	"TOFN",
	"TOLY",
	"TOPE",
	"TOWN",
	"TPE1",
	"TPE2",
	"TPE3",
	"TPE4",
	"TPOS",
	"TPRO",
	"TPUB",
	"TRCK",
	"TRSN",
	"TRSO",
	"TSOA",
	"TSOP",
	"TSOT",
	"TSRC",
	"TSSE",
	"TSST",
	"TXXX",
	"UFID",
	"USER",
	"USLT",
	"WCOM",
	"WCOP",
	"WOAF",
	"WOAR",
	"WOAS",
	"WORS",
	"WPAY",
	"WPUB",
	"WXXX",
	NULL
};

void string_write (const void *elem, FILE *file, void *data)
{

	fprintf (file, "%s", *(char **)elem);
}

int main(void)
{

	Hash *h;

	h = hash_new (40, NULL);

	char **ptr;
	for (ptr = a; *ptr != NULL; ptr++)
	{
		hash_insert (h, *ptr, *ptr);
	}

	hash_dump (h, stdout, string_write, NULL);

	for (ptr = a; *ptr != NULL; ptr++)
	{
		printf ("%s\n", (char *)hash_search (h, *ptr));
	}

	hash_free (h);

	return 0;
}
