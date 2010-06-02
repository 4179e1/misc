CC = gcc
CFLAGS = -Wall -O2
OBJ = libwpbase.so libwpstdc.so libwpsocket.so libwppthread.so libwpunix.so

all: $(OBJ)

$(OBJ) : %.so : %.c
	$(CC) -shared -o $@ $< $(CFLAGS)

clean:
	$(RM) $(OBJ)

install: all
	cp $(OBJ) /usr/lib/
	cp *.h	/usr/include/

HEADER = $(shell ls *.h)
uninstall:
	cd /usr/lib/&&rm $(OBJ)
	cd /usr/include/&&rm $(HEADER)
