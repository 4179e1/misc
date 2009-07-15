CC = gcc
O_FILE = dbb.o signal.o file.o debug.o database.o
GTK_FLAGS = $(shell pkg-config --libs --cflags gtk+-2.0)
SQL_FLAGS = -lsqlite3

dbb: $(O_FILE)
	$(CC) $(O_FILE) -o dbb -Wall -g -export-dynamic $(GTK_FLAGS) $(SQL_FLAGS)
dbb.o: dbb.c dbb.h comman.h dbb.xml
	$(CC) dbb.c -o dbb.o -c -Wall $(GTK_FLAGS)
dbb.xml: dbb.glade
	gtk-builder-convert dbb.glade dbb.xml
signal.o: signal.c signal.h comman.h
	$(CC) signal.c -o signal.o -c -Wall $(GTK_FLAGS)
file.o: file.c file.h comman.h
	$(CC) file.c -o file.o -c -Wall $(GTK_FLAGS)
debug.o: debug.c debug.h comman.h
	$(CC) debug.c -o debug.o -c -Wall $(GTK_FLAGS)
database.o: database.c database.h comman.h
	$(CC) database.c -o database.o -c -Wall $(GTK_FLAGS) $(SQL_FLAGS)

clean:
	rm $(O_FILE) dbb dbb.xml
