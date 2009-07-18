CC = gcc
OBJ = error.o wrapsock.o wrapunix.o main.o
MAIN = 1.2.c


all: $(OBJ)
	$(CC) $(OBJ) -o main -Wall

main.o: $(MAIN)
	$(CC) -c $< -o main.o -Wall

error.o: error.c unp.h
	$(CC) -c error.c -o error.o -Wall
wrapsock.o: wrapsock.c unp.h
	$(CC) -c $< -o $@ -Wall
wrapunix.o: wrapunix.c unp.h
	$(CC) -c $< -o $@ -Wall

clean:
	rm $(OBJ) main
