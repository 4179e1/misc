CC = gcc

GTK_FLAGS = $(shell pkg-config --cflags gtk+-2.0)
GTK_LINKER_FLAGS = $(shell pkg-config --libs gtk+-2.0)	
M_WINDOW_FLAGS = -mwindows

O_FILES = main.o treeview.o listview.o stack.o registry.o menu.o handler.o
HEADER = reg.h

reg: $(O_FILES) $(HEADER) Makefile
	$(CC) $(O_FILES) -o reg.exe -Wall -export-dynamic $(M_WINDOW_FLAGS) $(GTK_FLAGS) $(GTK_LINKER_FLAGS)
main.o: main.c $(HEADER)
	$(CC) main.c -o main.o -c -Wall $(GTK_FLAGS)
treeview.o: treeview.c $(HEADER)
	$(CC) treeview.c -o treeview.o -c -Wall $(GTK_FLAGS)
listview.o: listview.c $(HEADER)
	$(CC) listview.c -o listview.o -c -Wall $(GTK_FLAGS)
stack.o: stack.c $(HEADER)
	$(CC) stack.c -o stack.o -c -Wall
registry.o: registry.c $(HEADER)
	$(CC) registry.c -o registry.o -c -Wall $(GTK_FLAGS)
menu.o: menu.c $(HEADER)
	$(CC) menu.c -o menu.o -c -Wall $(GTK_FLAGS)
handler.o: handler.c $(HEADER)
	$(CC) handler.c -o handler.o -c -Wall $(GTK_FLAGS)
static: $(O_FILES) $(HEADER) Makefile
	$(CC) $(O_FILES) -o reg.exe -static -Wall -export-dynamic $(M_WINDOW_FLAGS) $(GTK_FLAGS) $(GTK_LINKER_FLAGS)
	

clean:
	del $(O_FILES) reg.exe
