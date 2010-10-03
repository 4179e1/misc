OBJ = test.o media.o my_marshaller.o cd.o cleanable.o
TARGET = media

PKGS = glib-2.0 gobject-2.0

GTK_FLAGS = $(shell pkg-config --cflags $(PKGS))
GTK_LIBS = $(shell pkg-config --libs $(PKGS))
CC = clang

CFLAGS += -Wall -O2 $(GTK_FLAGS)

all: $(OBJ)
	gcc -O2 -Wall -o $(TARGET) $^ $(CFLAGS) $(GTK_LIBS)

.PHONY : clean
clean:
	rm -rf $(OBJ) $(TARGET)
