SQUARE = square.h square_clnt.c square_svc.c square_xdr.c
SQUARE_OBJ = square_clnt.o square_xdr.o square_svc.o

all: $(SQUARE) $(SQUARE_OBJ) client server

$(SQUARE): square.x
	rpcgen -C $<

$(SQUARE_OBJ): %.o : %.c
	$(CC) -c $< -o $@ 
	
client: client.c
	$(CC) -o $@ client.c square_clnt.o square_xdr.o -lnsl `pkg-config --libs --cflags libwp0`

server: server.c
	$(CC) -o $@ server.c square_svc.o square_xdr.o `pkg-config --libs --cflags libwp0`

.PHONY: clean

clean:
	$(RM) -rf $(SQUARE) $(SQUARE_OBJ) client server
