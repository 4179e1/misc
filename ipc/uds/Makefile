TAR = echoc echos pass_descriptor
CFLAGS += -g -Wall

all: $(TAR)

$(TAR): % : %.c
	$(CC) $< -o $@ $(CFLAGS)

.PHONY: clean

clean:
	$(RM) -rf $(TAR)
