import socket
s = socket.socket()

host = socket.gethostname()
port = 1234
s.bind ((host, port))

s.listen(5)
while True:
    c, addr = s.accept()
    print ("Got connection from", addr)
    c.send ('Welcome')
    c.close()
