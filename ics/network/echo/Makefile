TAR = echoclient echoserver fork multiplex event thread prethread
CFLAGS += -g -Wall `pkg-config --cflags --libs libwp-0.0 wppthread-0.0`

all: prog

prog : $(TAR)

$(TAR) : % : %.c
	$(CC) $< -o $@ $(CFLAGS)

.PHONY: clean

clean:
	$(RM) -rf $(TAR)
