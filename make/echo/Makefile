CC = gcc
CFLAGS += -Wall -g
OBJ = a.o b.o

.PHONY: all clean
all: $(OBJ)

$(OBJ) : %.o : %.c
# the 2 instruct following oupouts "compiling $<".
# and it's the ouput of 'echo compiling $<'.
# normally, without the leadding '@',
# it'll output 3 lines inclueding the instrut itselves.
	@echo compiling $<
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) $(OBJ)
