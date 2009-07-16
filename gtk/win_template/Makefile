GTK_FLAGS = $(shell pkg-config --cflags "gtk+-2.0")
GTK_LIBS = $(shell pkg-config --libs "gtk+-2.0")
WINDOW_FLAG = -mwindows
CC = gcc

OBJ = main.o

test: $(OBJ)
	$(CC) $(OBJ) -o test -Wall -mwindows $(GTK_LIBS)
main.o: main.c
	$(CC) -c main.c -o main.o -Wall $(GTK_FLAGS)
	
