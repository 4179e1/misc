BIN = pipe fifo_serv fifo_cli pipe2 
RTBIN = mqctl mqselect signalrt
LIBS = util.o
CFLAGS = -g -Wall `pkg-config --cflags libwp0`
BINLIBS = $(CFLAGS) `pkg-config --libs libwp0`
RTFLAGS = $(BINLIBS) -lrt


all: libs bin rtbin mqthread

bin : $(BIN) 
rtbin: $(RTBIN)
libs : $(LIBS)

$(BIN): % : %.c $(LIBS) 
	$(CC) $< util.o -o $@  $(BINLIBS)

$(RTBIN): % : %.c $(LIBS) 
	$(CC) $< util.o -o $@  $(RTFLAGS)

$(LIBS): %.o : %.c %.h
	$(CC) $< -c -o $@ $(CFLAGS)

mqthread: mqthread.c $(LIBS)
	$(CC) $< -o $@ $(RTFLAGS) -lpthread

.PHONY: clean

clean:
	$(RM) -rf $(BIN) $(LIBS) $(RTBIN) mqthread
