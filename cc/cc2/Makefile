CC = gcc
O_FILE = main.o init_app.o signal.o
GTK_FLAGS = $(shell pkg-config --libs --cflags gtk+-2.0)

csc: $(O_FILE)
	 $(CC) $(O_FILE) -o csc -Wall -g -export-dynamic $(GTK_FLAGS)
main.o: main.c
	$(CC) main.c -o main.o -c -Wall $(GTK_FLAGS)
init_app.o: init_app.c main.xml
	$(CC) init_app.c -o init_app.o -c -Wall $(GTK_FLAGS)
signal.o: signal.c
	$(CC) signal.c -o signal.o -c -Wall $(GTK_FLAGS)

clean:
	rm $(O_FILE) csc
