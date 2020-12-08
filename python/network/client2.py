import socket
import sys

HOST = 'localhost'
PORT = 1234

s = None

for res in socket.getaddrinfo (HOST, PORT, socket.AF_UNSPEC, socket.SOCK_STREAM, 0, socket.AI_PASSIVE):
    af, socktype, proto, canonname, sa = res
    try:
        s = socket.socket (af, socktype, proto)
    except socket.error as msg:
        s = None
        continue
    
    try:
        s.connect (sa)
    except socket.error as msg:
        s.close()
        s = None
        continue

    break

if s is None:
    print 'could not open socket'
    sys.exit (1)

s.sendall ('Hello, world')
data = s.recv (1024)
print data
s.close ()
