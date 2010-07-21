AM_CFLAGS = -Wall

lib_LTLIBRARIES = libwpbase.la libwpstdc.la libwppthread.la libwpunix.la libwpsocket.la
libwpbase_la_SOURCES = libwpbase.c libwpbase.h
libwpstdc_la_SOURCES = libwpstdc.c libwpstdc.h libwpbase.h
libwppthread_la_SOURCES = libwppthread.c libwppthread.h libwpbase.h
libwpunix_la_SOURCES = libwpunix.c libwpunix.h libwpbase.h libwpunix_utils.c libwpunix_utils.h	libwpunix_rio.c libwpunix_rio.h
libwpsocket_la_SOURCES = libwpsocket.c libwpsocket.h libwpbase.h

include_HEADERS = libwp.h libwpbase.h libwppthread.c libwppthread.h libwpsocket.h libwpstdc.h libwpunix.h libwpunix_rio.h libwpunix_utils.h
