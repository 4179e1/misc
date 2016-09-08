BIN = pipe fifo_serv fifo_cli pipe2
LIBS = util.o
CFLAGS = -g -Wall `pkg-config --cflags libwp0`
BINFLAGS = $(CFLAGS) `pkg-config --libs libwp0`


all: libs bin thread

bin : $(BIN) 
libs : $(LIBS)
thread: $(THREAD_BIN)

$(BIN): % : %.c $(LIBS) 
	$(CC) $< util.o -o $@  $(BINFLAGS)

$(THREAD_BIN): % : %.c $(LIBS) 
	$(CC) $< util.o -o $@  $(THREAD_BINFLAGS)

$(LIBS): %.o : %.c %.h
	$(CC) $< -c -o $@ $(CFLAGS)

.PHONY: clean

clean:
	$(RM) -rf $(BIN) $(LIBS) $(THREAD_BIN)
