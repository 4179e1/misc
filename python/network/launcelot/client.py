import socket, sys, launcelot

def client (hostname, port):
    s = socket.socket (socket.AF_INET, socket.SOCK_STREAM)
    s.connect ((hostname, port))
    answers=[]
    for k in launcelot.qadict.keys():
        s.sendall (k)
        a = launcelot.recv_until (s, '.')
        answers.append(a)
    s.close()
    for a in answers:
        print a

if __name__ == '__main__':
    if not 2 <= len (sys.argv) <= 3:
        print >>sys.stderr, 'usage: client.py hostname [port]'
        sys.exit (2)
    port = int(sys.argv[2]) if len(sys.argv) == 3 else launcelot.PORT
    client (sys.argv[1], port)
