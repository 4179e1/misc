CC = gcc
BASE_PATH = ../../base/
CFLAGS = -Wall -I$(BASE_PATH)
OBJ = wppthread.o
TAR = posixthread.a

all: $(OBJ)
	ar rcs $(TAR) $(OBJ)

clean:
	rm $(OBJ) $(TAR)
