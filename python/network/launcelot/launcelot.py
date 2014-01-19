import socket, sys

PORT = 1234
qadict = {
'What is your name?': 'My name is Sir Launcelot of Camelot.',
'What is your quest?': 'To seek the Holy Grial.',
'What is your favorite color?': 'Blue.'}

def recv_until (sock, suffix):
    message = ''
    while not message.endswith (suffix):
        data = sock.recv(4096).strip('\n')
        if not data:
            raise EOFError ('socket closed before we saw %r' % suffix)
        message += data
    return message

def setup():
    interface = ''
    if len (sys.argv) >= 2:
        interface = sys.argv[1]
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.setsockopt (socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    sock.bind ((interface, PORT))
    sock.listen (1024)
    print 'Ready and listening at %r port %d' % (interface, PORT)
    return sock

