BIN = pipe fifo_serv fifo_cli pipe2 spooler semctl signalrt
RTBIN =  mqselect mqctl 
THREADBINS = producer_consumer rwlock 1p1c npnc multibuff
LIBS = util.o
OTHER = spoolernl
RTTHREAD = mqthread 
CFLAGS = -g -Wall `pkg-config --cflags libwp0 wppthread0 wprt0`
BINLIBS = $(CFLAGS) `pkg-config --libs libwp0`
RTLIBS = $(BINLIBS) `pkg-config --libs wprt0`
THREADLIBS = $(BINLIBS) `pkg-config --libs wppthread0`  
RTTHREADLIBS = $(THREADLIBS) `pkg-config --libs wprt0`

all: $(BIN) $(RTBIN) $(LIBS) $(THREADBINS) $(OTHER) $(RTTHREAD)

$(BIN): % : %.c $(LIBS) 
	$(CC) $< util.o -o $@  $(BINLIBS)

spoolernl : spooler.c $(LIBS) 
	$(CC) $< util.o -o $@  $(BINLIBS) -DNOLOCK

$(RTBIN): % : %.c $(LIBS) 
	$(CC) $< util.o -o $@  $(RTLIBS)

$(THREADBINS): % : %.c $(LIBS) 
	$(CC) $< util.o -o $@  $(THREADLIBS)

$(RTTHREAD): % : %.c $(LIBS) 
	$(CC) $< util.o -o $@  $(RTTHREADLIBS)

$(LIBS): %.o : %.c %.h
	$(CC) $< -c -o $@ $(CFLAGS)

#mqthread: mqthread.c $(LIBS)
#	$(CC) $< -o $@ $(RTLIBS) -lpthread

.PHONY: clean

clean:
	$(RM) -rf $(BIN) $(LIBS) $(RTBIN) $(THREADBINS) $(OTHER) 
