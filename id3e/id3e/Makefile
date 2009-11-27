TAR = id3e
OBJ = main.o id3e.o list.o callback.o id3.o id3v1.o enc.o gva.o gv1.o genre.o wrap.o

OPT = -DG_LOG_DOMAIN=\"ID3_Editor\" -Wall
GTKFLAGS = $(shell pkg-config --cflags gtk+-2.0 gmodule-2.0)
LIBS = $(shell pkg-config --libs gtk+-2.0 gmodule-2.0)

CC = gcc
CFLAGS =  $(GTKFLAGS) $(OPT) 

all: $(OBJ)
	$(CC) $(OBJ) -o $(TAR) $(CFLAGS) $(LIBS)

clean:
	rm $(TAR) $(OBJ)
