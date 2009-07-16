CC = gcc

GTK_FLAGS = $(shell pkg-config --cflags gtk+-2.0)
GTK_LINKER_FLAGS = $(shell pkg-config --libs gtk+-2.0)
M_WINDOW_FLAGS = -mwindows
WINSOCK_FLAGS = -lws2_32 -liphlpapi -lmswsock -lAdvapi32
THREAD_FLAGS = -lpthreadGC2

A_OUT = sniff	

O_FILES = main.o liststore.o check.o queue.o

$(A_OUT): $(O_FILES) $(HEADER) Makefile
	$(CC) $(O_FILES) -o $(A_OUT) -Wall -export-dynamic $(M_WINDOW_FLAGS) $(GTK_FLAGS) $(GTK_LINKER_FLAGS) $(WINSOCK_FLAGS) $(THREAD_FLAGS)
main.o: main.c $(HEADER)
	$(CC) main.c -o main.o -c -Wall $(GTK_FLAGS)
liststore.o: liststore.c $(HEADER)
	$(CC) liststore.c -o liststore.o -c -Wall $(GTK_FLAGS)
check.o: check.c
	$(CC) check.c -o check.o -c -Wall $(GTK_FLAGS)
queue.o: queue.c
	$(CC) queue.c -o queue.o -c -Wall

clean:
	del $(O_FILES) $(A_OUT)
