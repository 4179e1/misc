BIN = pipe fifo_serv fifo_cli pipe2 spooler
RTBIN = mqctl mqselect signalrt semctl
THREADBINS = producer_consumer rwlock
LIBS = util.o
OTHER = mqthread spoolernl
CFLAGS = -g -Wall `pkg-config --cflags libwp0 wppthread0`
BINLIBS = $(CFLAGS) `pkg-config --libs libwp0`
RTLIBS = $(BINLIBS) -lrt
THREADLIBS = $(BINLIBS) `pkg-config --libs wppthread0` -lpthread 

all: $(BIN) $(RTBIN) $(LIBS) $(THREADBINS) $(OTHER)

$(BIN): % : %.c $(LIBS) 
	$(CC) $< util.o -o $@  $(BINLIBS)

spoolernl : spooler.c $(LIBS) 
	$(CC) $< util.o -o $@  $(BINLIBS) -DNOLOCK

$(RTBIN): % : %.c $(LIBS) 
	$(CC) $< util.o -o $@  $(RTLIBS)

$(THREADBINS): % : %.c $(LIBS) 
	$(CC) $< util.o -o $@  $(THREADLIBS)

$(LIBS): %.o : %.c %.h
	$(CC) $< -c -o $@ $(CFLAGS)

mqthread: mqthread.c $(LIBS)
	$(CC) $< -o $@ $(RTLIBS) -lpthread

.PHONY: clean

clean:
	$(RM) -rf $(BIN) $(LIBS) $(RTBIN) $(THREADBINS) $(OTHER) 
