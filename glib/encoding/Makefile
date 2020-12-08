FLAG = $(shell pkg-config --cflags glib-2.0)
LIB = $(shell pkg-config --libs glib-2.0)

all: main.c
	gcc main.c $(FLAG) $(LIB) -Wall
