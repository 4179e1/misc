CC = gcc

GTK_FLAGS = $(shell pkg-config --cflags gtk+-2.0)
GTK_LINKER_FLAGS = $(shell pkg-config --libs gtk+-2.0)	
M_WINDOW_FLAGS = -mwindows
WINSOCK_FLAGS = -lws2_32 -liphlpapi -lmswsock -lAdvapi32

O_FILES = main.o callback.o socket.o scan.o
HEADER = collection.h

collection: $(O_FILES) $(HEADER)
	$(CC) $(O_FILES) -o collection.exe -Wall -export-dynamic $(GTK_FLAGS) $(GTK_LINKER_FLAGS) $(WINSOCK_FLAGS)
main.o: main.c $(HEADER) callback.h
	$(CC) main.c -o main.o -c -Wall $(GTK_FLAGS)
callback.o: callback.c callback.h socket.h $(HEADER)
	$(CC) callback.c -o callback.o -c -Wall $(GTK_FLAGS)
socket.o: socket.c socket.h
	$(CC) socket.c -o socket.o -c -Wall
scan.o: scan.c scan.h
	$(CC) scan.c -o scan.o -c -Wall $(GTK_FLAGS)

clean:
	del $(O_FILES) collection.exe
