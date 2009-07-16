CC = gcc

GTK_FLAGS = $(shell pkg-config --cflags gtk+-2.0)
GTK_LINKER_FLAGS = $(shell pkg-config --libs gtk+-2.0)	
M_WINDOW_FLAGS = -mwindows
ODBC_FLAGS = -lodbc32

O_FILES = main.o liststore.o sql.o

odbc: $(O_FILES) $(HEADER) Makefile
	$(CC) $(O_FILES) -o odbc.exe -Wall -export-dynamic  $(GTK_FLAGS) $(GTK_LINKER_FLAGS) $(ODBC_FLAGS)
main.o: main.c $(HEADER)
	$(CC) main.c -o main.o -c -Wall $(GTK_FLAGS)
liststore.o: liststore.c
	$(CC) liststore.c -o liststore.o -c -Wall $(GTK_FLAGS)
sql.o: sql.c
	$(CC) sql.c -o sql.o -c -Wall $(GTK_FLAGS)

clean:
	del $(O_FILES) reg.exe
