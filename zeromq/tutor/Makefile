SUFFIX=c
SRC=$(shell ls *.$(SUFFIX))
TAR=$(SRC:%.$(SUFFIX)=%)
CFLAGS=-g -Wall
LDFLAGS+=-lzmq

all: $(TAR)

$(TAR): %: %.$(SUFFIX)
	$(CC) $< -o $@ $(CFLAGS) $(LDFLAGS)
	
.PHONY: clean
clean:
	$(RM) -rf $(TAR) *.ipc
