CC = gcc
BASE_PATH = ../../base/
CFLAGS = -Wall -I$(BASE_PATH)
OBJ = wpfileio.o
TAR = posixio.a

all: $(OBJ)
	ar rcs $(TAR) $(OBJ)

clean:
	rm $(OBJ) $(TAR)
