OBJ = base.o wrap.o
CC = gcc
CFLAGS = -Wall

all: $(OBJ)
	ar rcs libbase.a $(OBJ)

test:
	$(CC) test.c -o test -Wall -L. -lbase
