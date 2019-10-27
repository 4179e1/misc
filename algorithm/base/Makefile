OBJ = base.o wrap.o int_func.o
CC = gcc
CFLAGS = -Wall

all: $(OBJ)
	ar rcs libbase.a $(OBJ)

test:
	$(CC) test.c -o test -Wall -L. -lbase

clean:
	$(RM) -rf *.o *.a
