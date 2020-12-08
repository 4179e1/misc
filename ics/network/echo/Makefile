TAR = echoclient echoserver fork multiplex event thread prethread epoll
CFLAGS += -g -Wall `pkg-config --cflags --libs libwp0 wppthread0`

all: prog

prog : $(TAR)

$(TAR) : % : %.c
	$(CC) $< -o $@ $(CFLAGS)

.PHONY: clean

clean:
	$(RM) -rf $(TAR)
