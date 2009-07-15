CC = gcc
O_FILE = dbb.o signal.o file_menu.o edit_menu.o debug_menu.o other_menu.o database.o
COMMAN_H = comman.h
GTK_FLAGS = $(shell pkg-config --libs --cflags gtk+-2.0)
SQL_FLAGS = -lsqlite3

dbb: $(O_FILE)
	$(CC) $(O_FILE) -o dbb -Wall -g -export-dynamic $(GTK_FLAGS) $(SQL_FLAGS)
dbb.o: dbb.c dbb.h $(COMMAN_H) dbb.xml Makefile
	$(CC) dbb.c -o dbb.o -c -Wall $(GTK_FLAGS)
dbb.xml: dbb.glade
	gtk-builder-convert dbb.glade dbb.xml
signal.o: signal.c signal.h edit_menu.h $(COMMAN_H)
	$(CC) signal.c -o signal.o -c -Wall $(GTK_FLAGS)
file_menu.o: file_menu.c file_menu.h signal.h $(COMMAN_H)
	$(CC) file_menu.c -o file_menu.o -c -Wall $(GTK_FLAGS)
edit_menu.o: edit_menu.c edit_menu.h $(COMMAN_H)
	$(CC) edit_menu.c -o edit_menu.o -c -Wall $(GTK_FLAGS)
debug_menu.o: debug_menu.c debug_menu.h $(COMMAN_H)
	$(CC) debug_menu.c -o debug_menu.o -c -Wall $(GTK_FLAGS)
other_menu.o: other_menu.c other_menu.h $(COMMAN_H)
	$(CC) other_menu.c -o other_menu.o -c -Wall $(GTK_FLAGS)
database.o: database.c database.h $(COMMAN_H)
	$(CC) database.c -o database.o -c -Wall $(GTK_FLAGS)

clean:
	rm $(O_FILE) dbb dbb.xml
