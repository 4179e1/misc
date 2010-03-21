GTK_FLAGS = $(shell pkg-config --cflags "gtk+-2.0")
GTK_LIBS = $(shell pkg-config --libs "gtk+-2.0")
WINDOW_FLAG = -mwindows
CC = gcc

OBJ = png pdf svg gtk

all: $(OBJ)

$(OBJ):	% : %.c
	$(CC) $< -o $@ -Wall $(GTK_FLAGS) $(GTK_LIBS)
