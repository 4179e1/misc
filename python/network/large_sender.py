import IN, socket, sys
s = socket.socket (socket.AF_INET, socket.SOCK_DGRAM)
MAX = 65535
PORT = 1060

if len (sys.argv) != 2:
    print >> sys.stderr, 'usage: large_sender.py host'
    sys.exit (2)

hostname = sys.argv[1]
s.connect ((hostname, PORT))
s.setsockopt (socket.IPPROTO_IP, IN.IP_MTU_DISCOVER, IN.IP_PMTUDISC_DO)
try:
    s.send ('#' * 5000)
except socket.error:
    print 'The message did not make it'
    option = getattr (IN, "IP_MTU", 14)
    print 'MTU:', s.getsockopt (socket.IPPROTO_IP, option)
else:
    print 'The big message was sent!'
