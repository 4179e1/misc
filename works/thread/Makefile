CC = gcc
GTK_FLAGS = $(shell pkg-config --cflags gtk+-2.0 gthread-2.0)
GTK_LINKER_FLAGS = $(shell pkg-config --libs gtk+-2.0 gthread-2.0)	

collection: test.c
	$(CC) test.c -o test -Wall -export-dynamic $(GTK_FLAGS) $(GTK_LINKER_FLAGS) -lpthreadGC2
