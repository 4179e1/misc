import socket, sys
if len(sys.argv) != 2:
    print >> sys.stderr, 'usage: www_pingpy <hostname>'
    sys.exit (2)

hostname = sys.argv[1]
try:
    infolist = socket.getaddrinfo (hostname, 'www', 0, socket.SOCK_STREAM, 0, socket.AI_ADDRCONFIG|socket.AI_V4MAPPED|socket.AI_CANONNAME)
except socket.gaierror as e:
    print 'Name service failure:', e
    sys.exit (1)

info = infolist[0]
print 'Debug:', info

canonical = info[3]
socketname = info[4]
ip = socketname[0]

if not canonical:
    print 'WARNING! The IP address', ip, 'has no reverse name'
    sys.exit(1)

print hostname, 'has IP address', ip
print ip, 'has the canonical hostname', canonical

forward = hostname.lower().split('.')
reverse = canonical.lower().split('.')
if forward == reverse:
    print 'Wow, the names agree completely!'
    sys.exit(0)

length = min(len(forward), len(reverse))
if (forward[-length:] == reverse[-length:]): # equal
    print 'The forward and reverse names have same domain'
elif (len(forward) == len (reverse)
    and forward[-length+1:] == reverse[-length+1:] # mail.poetpalace.org == www.poetpalace.org
    and len(forward[-2] > 2)):          # avoid '.co.uk'
    print 'The forward and reverse names have a lot in common'
else:
    print 'WARNING! The reverse name belongs to a different organization'
