AM_CFLAGS = -O2 -Wall -DDATADIR='"$(datadir)"' @GTK_FLAGS@

bin_PROGRAMS = id3e
id3e_SOURCES = callback.c genre.c gva.c id3e.c list.c wrap.c enc.c gv1.c id3.c id3v1.c main.c
id3e_LDADD = @GTK_LIBS@

noinst_HEADERS = callback.h genre.h gva.h id3.h list.h enc.h gv1.h id3e.h id3v1.h wrap.h

id3edir = @prefix@/share/id3e
id3e_DATA = id3e.glade

EXTRA_DIST = $(id3e_DATA)
