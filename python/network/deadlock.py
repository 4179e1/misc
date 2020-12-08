import socket, sys
s = socket.socket (socket.AF_INET, socket.SOCK_STREAM)

HOST = '127.0.0.1'
PORT = 1060

if sys.argv[1:] == ['server']:
    s.setsockopt (socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind ((HOST, PORT))
    s.listen (1)

    while True:
        print 'Listening at', s.getsockname()
        sc, sockname = s.accept()
        print 'Processing up to 1024 bytes at a time from', sockname
        n = 0
        while True:
            message = sc.recv (1024)
            if not message:
                break
            sc.sendall (message.upper())
            n += len (message)
            print '\r%d bytes processed so far' % (n,),
            sys.stdout.flush()
        print
        sc.close()
        print 'Completed processing'

elif len(sys.argv) == 3 and sys.argv[1] == 'client' and sys.argv[2].isdigit():
    bytes = int(sys.argv[2])
    message = 'capitalize this!'

    print 'Sending', bytes, 'bytes of data, in chunks of 16 bytes'
    s.connect ((HOST, PORT))

    sent = 0
    while sent < bytes:
        s.sendall (message)
        sent += len (message)
        print '\r%d bytes send' % (sent,),
        sys.stdout.flush()
    print 
    s.shutdown (socket.SHUT_WR)

    print 'Receving all tghe data the server sends back'

    received = 0
    while True:
        data = s.recv (42)
        if not received:
            print 'The first data received says', repr (data)
        received += len (data)
        if not data:
            break
        print '\r%d bytes received' % (received,),
    s.close()
else:
    print >> sys.stderr, 'usage...'

    
