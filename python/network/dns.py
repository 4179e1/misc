from pprint import pprint
from socket import getaddrinfo
import socket

print '- port only'
pprint (getaddrinfo (None, 'ssh'))
print
print '- port, family'
pprint (getaddrinfo (None, 'ssh', socket.AF_INET))
print
print '- port, socktype'
pprint (getaddrinfo (None, 'ssh', 0, socket.SOCK_STREAM))
print
print '- host, port, family'
pprint (getaddrinfo ('poetpalace.org', 'www', socket.AF_INET))
print
print '- host, port, socktype'
pprint (getaddrinfo ('poetpalace.org', 'www', 0, socket.SOCK_STREAM))
print
print '- host, port, family, socktype'
pprint (getaddrinfo ('poetpalace.org', 'www', socket.AF_INET, socket.SOCK_STREAM))
print
print '- iana '
pprint (getaddrinfo ('iana.org', 'www', 0, socket.SOCK_STREAM, 0))
print
pprint (getaddrinfo ('iana.org', 'www', 0, socket.SOCK_STREAM, 0, socket.AI_ADDRCONFIG))
print
pprint (getaddrinfo ('iana.org', 'www', 0, socket.SOCK_STREAM, 0, socket.AI_CANONNAME))
