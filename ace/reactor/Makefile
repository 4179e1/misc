OBJ=client server
CFLAGS+=-g -Wall
LDFLAGS+=-lstdc++ -lACE

all: $(OBJ)

$(OBJ): % : %.cpp
	echo $(CC) -c $< -o $@ $(CFLAGS) $(LDFLAGS)
