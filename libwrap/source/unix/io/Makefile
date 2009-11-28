CC = gcc
CFLAGS = -Wall -std=c99
OBJ = wpfileio.o wpfileutilities.o
TAR = unixio.a

all: $(OBJ)
	ar rcs $(TAR) $(OBJ)

clean:
	rm $(OBJ) $(TAR)
