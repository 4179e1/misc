import socket
s = socket.socket()

host = 'localhost'
port = 1234
s.bind ((host, port))

s.listen(5)
while True:
    c, addr = s.accept()
    print ("Got connection from", addr)
    buffer = c.recv (8192)
    while buffer:
        c.send (buffer)
        buffer = c.recv (8192)
    c.close()
