BIN = client fork iterate prefork prefork2 prefork_flock
THREAD_BIN = prefork_pthread pthread prethread prethread_main
LIBS = lib.o
CFLAGS = -g -Wall `pkg-config --cflags libwp0 wppthread0` -DNDEBUG
BINFLAGS = $(CFLAGS) `pkg-config --libs libwp0`
THREAD_BINFLAGS = $(BINFLAGS) `pkg-config --libs  wppthread0`


all: libs bin thread

bin : $(BIN) 
libs : $(LIBS)
thread: $(THREAD_BIN)

$(BIN): % : %.c $(LIBS) 
	$(CC) $< lib.o -o $@  $(BINFLAGS)

$(THREAD_BIN): % : %.c $(LIBS) 
	$(CC) $< lib.o -o $@  $(THREAD_BINFLAGS)

$(LIBS): %.o : %.c %.h
	$(CC) $< -c -o $@ $(CFLAGS)

.PHONY: clean

clean:
	$(RM) -rf $(BIN) $(LIBS) $(THREAD_BIN)
