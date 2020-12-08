import sys, socket

s = socket.socket (socket.AF_INET, socket.SOCK_DGRAM)
# it seems that on linux, only client need this
# servers will get the broadcast packet even if they didn't enable it
s.setsockopt (socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

MAX = 65535
PORT = 1060

if 2 <= len (sys.argv) <= 3 and sys.argv[1] == 'server':
    network = sys.argv[2] if len (sys.argv) == 3 else ''
    s.bind ((network, PORT))
    print 'Listening for broadcasts at', s.getsockname()
    while True:
        data, address = s.recvfrom (MAX)
        print 'The client at %r says: %r' % (address, data)
elif len (sys.argv) == 3 and sys.argv[1] == 'client':
    network = sys.argv[2]    
    s.sendto ('Broadcast message!', (network, PORT))
else:
    print 'usage ...'
    sys.exit(2)
