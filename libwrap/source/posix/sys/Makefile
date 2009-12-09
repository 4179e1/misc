CC = gcc
BASE_PATH = ../../base/
CFLAGS = -Wall -I$(BASE_PATH)
OBJ = wpsys.o wpsysutilities.o
TAR = posixsys.a

all: $(OBJ)
	ar rcs $(TAR) $(OBJ)

clean:
	rm $(OBJ) $(TAR)
