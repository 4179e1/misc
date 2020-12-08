TAR = usb

LIB_PATH = /usr/src/lib/obj-ack
SYSUTIL = sysutil
SYSLIB = sys

OBJ= uhci.o usb.o io.o


$(TAR): $(OBJ)
	cc $(OBJ) -o $(TAR) -L$(LIB_PATH) -l$(SYSLIB)
debug: $(OBJ)
	cc $(OBJ) -o $(TAR) -L$(LIB_PATH) -l$(SYSUTIL) -l$(SYSLIB)
uhci.o: uhci.c uhci.h
	cc -c uhci.c -o uhci.o
usb.o: usb.c usb.h
	cc -c usb.c -o usb.o
io.o: io.c io.h
	cc -c io.c -o io.o

clean:
	rm $(TAR) $(OBJ)

install: $(TAR) 
	cp usb /usr/sbin

run: $(TAR)
	service up /usr/src/drivers/usb/usb -dev /dev/usbkey

ps:
	ps -x | grep usb
