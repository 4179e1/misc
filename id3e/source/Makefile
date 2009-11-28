TAR = id3e
OBJ = main.o id3e.o list.o callback.o id3.o id3v1.o enc.o gva.o gv1.o genre.o wrap.o

OPT = -DG_LOG_DOMAIN=\"ID3_Editor\" -Wall
GTKFLAGS = $(shell pkg-config --cflags gtk+-2.0 gmodule-2.0)
LIBS = $(shell pkg-config --libs gtk+-2.0 gmodule-2.0)

INSTALL_PATH = /usr/share/id3e

CC = gcc
CFLAGS =  $(GTKFLAGS) $(OPT) 

all: $(OBJ)
	$(CC) $(OBJ) -o $(TAR) $(CFLAGS) $(LIBS)

install:
	mkdir -p $(INSTALL_PATH)
	cp $(TAR) $(INSTALL_PATH)
	cp $(TAR).glade $(INSTALL_PATH)
	cp $(TAR).sh /usr/bin/$(TAR)
	chmod +x /usr/bin/$(TAR)

uninstall:
	rm /usr/bin/$(TAR)
	rm $(INSTALL_PATH)/$(TAR)
	rm $(INSTALL_PATH)/$(TAR).glade

clean:
	rm $(TAR) $(OBJ)
