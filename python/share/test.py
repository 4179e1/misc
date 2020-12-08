from xmlrpclib import *

try:
	mypeer = ServerProxy ('http://localhost:4242')
	print mypeer.query('file2')
except:
	print 'oops, not found'

otherpeer = ServerProxy ('http://localhost:4243')
print otherpeer.query('file2')

mypeer.hello ('http://localhost:4243')
print mypeer.query('file2')

mypeer.fetch('file2', 'secret1')

