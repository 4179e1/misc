CC = gcc
BASE_PATH = ../base/
CFLAGS = -Wall -I$(BASE_PATH)
OBJ = wpsocket.o
TAR = socket.a

all: $(OBJ)
	ar rcs $(TAR) $(OBJ)

clean:
	rm $(OBJ) $(TAR)
