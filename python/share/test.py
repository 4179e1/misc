from xmlrpclib import *

mypeer = ServerProxy ('http://localhost:4242')
code, data = mypeer.query('file2')
print 'CODE: %d, DATA: %s' % (code, data)

otherpeer = ServerProxy ('http://localhost:4243')
code, data = otherpeer.query('file2')
print 'CODE: %d, DATA: %s' % (code, data)

mypeer.hello ('http://localhost:4243')
code, data = mypeer.query('file2')
print 'CODE: %d, DATA: %s' % (code, data)

mypeer.fetch('file2', 'secret1')

