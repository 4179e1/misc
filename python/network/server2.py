import socket
import sys

HOST = None
PORT = 1234

s = None

for res in socket.getaddrinfo (HOST, PORT, socket.AF_UNSPEC, socket.SOCK_STREAM, 0, socket.AI_PASSIVE):
    af, socktype, proto, canonname, sa = res
    print res
    try:
        s = socket.socket (af, socktype, proto)
    except sock.error as msg:
        s = None
        continue
    
    try:
        s.bind (sa)
        s.listen (5)
    except socket.error as msg:
        s.close()
        s = None
        continue
   break

if s is None:
    print 'could not open socket'
    sys.exit(1)
while True:
    conn, addr = s.accept()
    print 'Connected by', addr
    data = conn.recv (1024)
    if not data: break
    conn.send (data)
    conn.close()
