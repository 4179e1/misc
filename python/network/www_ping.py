import socket, sys
if len(sys.argv) != 2:
    print >> sys.stderr, 'usage: www_pingpy <hostname_or_ip>'
    sys.exit (2)

hostname_or_ip = sys.argv[1]
try:
    infolist = socket.getaddrinfo (hostname_or_ip, 'www', 0, socket.SOCK_STREAM, 0, socket.AI_ADDRCONFIG|socket.AI_V4MAPPED|socket.AI_CANONNAME)
except socket.gaierror as e:
    print 'Name service failure:', e
    sys.exit (1)

info = infolist[0]
socket_args = info[0:3]
address = info[4]
s = socket.socket(*socket_args)
try:
    s.connect (address)
except socekt.error as e:
    print 'Network failure:', e
else:
    print 'SUccess: host', info[3], 'is listening on port 80'
