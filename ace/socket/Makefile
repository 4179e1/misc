OBJ=client server
CFLAGS+=-g -Wall
LDFLAGS+=-lstdc++ -lACE

all: $(OBJ)

$(OBJ): % : %.cpp
	$(CC) $< -o $@ $(CFLAGS) $(LDFLAGS)

.PHONY: clean
clean:
	$(RM) -rf $(OBJ)
