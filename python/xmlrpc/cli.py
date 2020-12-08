#/usr/bin/env python
import xmlrpclib
import sys

if len(sys.argv) < 2: 
	sys.stderr.write ("Usage: %s <seconds>\n" % sys.argv[0])
	sys.exit (1)

s = xmlrpclib.ServerProxy ('http://localhost:8000')
print s.system.listMethods()
print s.sleep (int(sys.argv[1]))
