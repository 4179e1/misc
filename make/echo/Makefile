CC = gcc
CFLAGS += -Wall -g
OBJ = a.o b.o

.PHONY: all clean
all: $(OBJ)

$(OBJ) : %.o : %.c
	@echo compiling $<
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) $(OBJ)
