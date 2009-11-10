#include <gtk/gtk.h>
#include "genre.h"

gchar *genre[] = 
{
	"Blues",			/* 0   */
	"Classic Rock",		/* 1   */
	"Country",          /* 2   */
	"Dance",            /* 3   */
	"Disco",			/* 4   */
	"Funk",             /* 5   */
	"Grunge",           /* 6   */
	"Hip-Hop",          /* 7   */
	"Jazz",             /* 8   */
	"Metal",            /* 9   */
	"New Age",          /* 10  */
	"Oldies",           /* 11  */
	"Other",            /* 12  */
	"Pop",              /* 13  */
	"R&B",              /* 14  */
	"Rap",              /* 15  */
	"Reggae",           /* 16  */
	"Rock",             /* 17  */
	"Techno",           /* 18  */
	"Industrial",       /* 19  */
	"Alternative",      /* 20  */
	"Ska",              /* 21  */
	"Death Metal",      /* 22  */
	"Pranks",           /* 23  */
	"Soundtrack",       /* 24  */
	"Euro-Techno",      /* 25  */
	"Ambient",          /* 26  */
	"Trip-Hop",         /* 27  */
	"Vocal",            /* 28  */
	"Jazz+Funk",        /* 29  */
	"Fusion",           /* 30  */
	"Trance",           /* 31  */
	"Classical",        /* 32  */
	"Instrumental",     /* 33  */
	"Acid",             /* 34  */
	"House",            /* 35  */
	"Game",             /* 36  */
	"Sound Clip",       /* 37  */
	"Gospel",           /* 38  */
	"Noise",            /* 39  */
	"Alternative Rock", /* 40  */
	"Bass",             /* 41  */
	"Punk",             /* 42  */
	"Space",            /* 43  */
	"Meditative",       /* 44  */
	"Instrumental Pop", /* 45  */
	"Instrumental Rock",/* 46  */
	"Ethnic",           /* 47  */
	"Gothic",           /* 48  */
	"Darkwave",         /* 49  */
	"Techno-Industrial",/* 50  */
	"Electronic",       /* 51  */
	"Pop-Folk",         /* 52  */
	"Eurodance",        /* 53  */
	"Dream",            /* 54  */
	"Southern Rock",    /* 55  */
	"Comedy",           /* 56  */
	"Cult",             /* 57  */
	"Gangsta",          /* 58  */
	"Top 40",           /* 59  */
	"Christian Rap",    /* 60  */
	"Pop/Funk",         /* 61  */
	"Jungle",           /* 62  */
	"Native US",        /* 63  */
	"Cabaret",          /* 64  */
	"New Wave",         /* 65  */
	"Psychadelic",      /* 66  */
	"Rave",             /* 67  */
	"Showtunes",        /* 68  */
	"Trailer",          /* 69  */
	"Lo-Fi",            /* 70  */
	"Tribal",           /* 71  */
	"Acid Punk",        /* 72  */
	"Acid Jazz",        /* 73  */
	"Polka",            /* 74  */
	"Retro",            /* 75  */
	"Musical",          /* 76  */
	"Rock & Roll",      /* 77  */
	"Hard Rock",        /* 78  */
	"Folk",             /* 79  */
	"Folk-Rock",        /* 80  */
	"National Folk",    /* 81  */
	"Swing",            /* 82  */
	"Fast Fusion",      /* 83  */
	"Bebob",            /* 84  */
	"Latin",            /* 85  */
	"Revival",          /* 86  */
	"Celtic",           /* 87  */
	"Bluegrass",        /* 88  */
	"Avantgarde",       /* 89  */
	"Gothic Rock",      /* 90  */
	"Progressive Rock", /* 91  */
	"Psychedelic Rock", /* 92  */
	"Symphonic Rock",   /* 93  */
	"Slow Rock",        /* 94  */
	"Big Band",         /* 95  */
	"Chorus",           /* 96  */
	"Easy Listening",   /* 97  */
	"Acoustic",         /* 98  */
	"Humour",           /* 99  */
	"Speech",           /* 100 */
	"Chanson",          /* 101 */
	"Opera",            /* 102 */
	"Chamber Music",    /* 103 */
	"Sonata",           /* 104 */
	"Symphony",         /* 105 */
	"Booty Bass",       /* 106 */
	"Primus",           /* 107 */
	"Porn Groove",      /* 108 */
	"Satire",           /* 109 */
	"Slow Jam",         /* 110 */
	"Club",             /* 111 */
	"Tango",            /* 112 */
	"Samba",            /* 113 */
	"Folklore",         /* 114 */
	"Ballad",           /* 115 */
	"Power Ballad",     /* 116 */
	"Rhytmic Soul",     /* 117 */
	"Freestyle",        /* 118 */
	"Duet",             /* 119 */
	"Punk Rock",        /* 120 */
	"Drum Solo",        /* 121 */
	"Acapella",         /* 122 */
	"Euro-House",       /* 123 */
	"Dance Hall",       /* 124 */
	"Goa",              /* 125 */
	"Drum & Bass",      /* 126 */
	"Club-House",       /* 127 */
	"Hardcore",         /* 128 */
	"Terror",           /* 129 */
	"Indie",            /* 130 */
	"BritPop",          /* 131 */
	"Negerpunk",        /* 132 */
	"Polsk Punk",       /* 133 */
	"Beat",             /* 134 */
	"Christian Gangsta",/* 135 */
	"Heavy Metal",      /* 136 */
	"Black Metal",      /* 137 */
	"Crossover",        /* 138 */
	"Contemporary C",   /* 139 */
	"Christian Rock",   /* 140 */
	"Merengue",         /* 141 */
	"Salsa",            /* 142 */
	"Thrash Metal",     /* 143 */
	"Anime",            /* 144 */
	"JPop",             /* 145 */
	"SynthPop",         /* 146 */
	NULL				/* 147 */
};

void genre_list_init (GtkListStore *liststore)
{
	gchar **ptr;
	GtkTreeIter iter;

	for (ptr = genre; *ptr != NULL; ptr++)
	{
		gtk_list_store_append (liststore, &iter);
		gtk_list_store_set (liststore, &iter,
				0, *ptr,
				-1);
	}

}

gchar *get_genre (int id)
{
	return genre[id];
}
