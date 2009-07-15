CC = gcc
O_FILE = main.o handler.o file_menu.o new_file.o edit_menu.o debug_menu.o other.o database.o tree.o
HEADER = database_builder.h
GTK_FLAGS = $(shell pkg-config --libs --cflags gtk+-2.0)
SQL_FLAGS = -lsqlite3

database_builder: $(O_FILE)
	$(CC) $(O_FILE) -o database_builder -Wall -g -export-dynamic $(GTK_FLAGS) $(SQL_FLAGS)
main.o: $(HEADER) main.c main.h
	$(CC) main.c -o main.o -c -Wall $(GTK_FLAGS) $(GLADE_FLAGS)
handler.o: $(HEADER) handler.c handler.h
	$(CC) handler.c -o handler.o -c -Wall $(GTK_FLAGS)
file_menu.o: $(HEADER) file_menu.c file_menu.h
	$(CC) file_menu.c -o file_menu.o -c -Wall $(GTK_FLAGS) $(SQL_FLAGS)
new_file.o: $(HEADER) new_file.c new_file.h
	$(CC) new_file.c -o new_file.o -c -Wall $(GTK_FLAGS)
edit_menu.o: $(HEADER) edit_menu.c edit_menu.h
	$(CC) edit_menu.c -o edit_menu.o -c -Wall $(GTK_FLAGS)
debug_menu.o: $(HEADER) debug_menu.c debug_menu.h
	$(CC) debug_menu.c -o debug_menu.o -c -Wall $(GTK_FLAGS)
other.o: $(HEADER) other.c other.h
	$(CC) other.c -o other.o -c -Wall $(GTK_FLAGS)
database.o: $(HEADER) database.c database.h
	$(CC) database.c -o database.o -c -Wall $(GTK_FLAGS) $(SQL_FLAGS)
tree.o: $(HEADER) tree.c tree.h
	$(CC) tree.c -o tree.o -c -Wall $(GTK_FLAGS);

clean:
	rm $(O_FILE) database_builder
