OPT = $(shell pkg-config --libs --cflags glib-2.0)
all: main.c
	gcc main.c -o count -O2 -Wall $(OPT)
