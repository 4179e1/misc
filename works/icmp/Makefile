CC = gcc

GTK_FLAGS = $(shell pkg-config --cflags gtk+-2.0)
GTK_LINKER_FLAGS = $(shell pkg-config --libs gtk+-2.0)
M_WINDOW_FLAGS = -mwindows
WINSOCK_FLAGS = -lws2_32 -liphlpapi -lmswsock -lAdvapi32
THREAD_FLAGS = -lpthreadGC2

A_OUT = icmp	

O_FILES = main.o liststore.o ping.o trace.o option.o socket.o handler.o queue.o stop.o

$(A_OUT): $(O_FILES) $(HEADER) Makefile
	$(CC) $(O_FILES) -o $(A_OUT) -Wall -export-dynamic $(M_WINDOW_FLAGS) $(GTK_FLAGS) $(GTK_LINKER_FLAGS) $(ODBC_FLAGS) $(WINSOCK_FLAGS) $(THREAD_FLAGS)
main.o: main.c $(HEADER)
	$(CC) main.c -o main.o -c -Wall $(GTK_FLAGS)
liststore.o: liststore.c $(HEADER)
	$(CC) liststore.c -o liststore.o -c -Wall $(GTK_FLAGS)
ping.o: ping.c $(HEADER)
	$(CC) ping.c -o ping.o -c -Wall $(GTK_FLAGS)
trace.o: trace.c $(HEADER)
	$(CC) trace.c -o trace.o -c -Wall $(GTK_FLAGS)
option.o: option.c $(HEADER)
	$(CC) option.c -o option.o -c -Wall $(GTK_FLAGS)
socket.o: socket.c $(HEADER)
	$(CC) socket.c -o socket.o -c -Wall	
handler.o: handler.c $(HEADER)
	$(CC) handler.c -o handler.o -c -Wall $(GTK_FLAGS)
queue.o: queue.c $(HEADER)
	$(CC) queue.c -o queue.o -c -Wall
stop.o: stop.c $(HEADER)
	$(CC) stop.c -o stop.o -c -Wall $(GTK_FLAGS)

clean:
	del $(O_FILES) $(A_OUT)
