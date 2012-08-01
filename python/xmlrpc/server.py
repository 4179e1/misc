#/usr/bin/env python
import os
from SimpleXMLRPCServer import SimpleXMLRPCServer
from SimpleXMLRPCServer import SimpleXMLRPCRequestHandler

class RequestHandler (SimpleXMLRPCRequestHandler):
	rpc_paths = ('/RPC2',)

	def do_GET(self):
		try:
			f = open(os.getcwd() + '/' + self.path) #self.path has /test.html
	#note that this potentially makes every file on your computer readable by the internet
	
			self.send_response(200)
			self.send_header('Content-type',	'text/html')
			self.end_headers()
			self.wfile.write(f.read())
			f.close()
			return

		except IOError:
			self.send_error(404,'File Not Found: %s' % self.path)

server = SimpleXMLRPCServer (('localhost', 8000), requestHandler = RequestHandler)
server.register_introspection_functions()

server.register_function(pow)

def adder_function (x, y):
	return x + y
server.register_function (adder_function, 'add')

class MyFuncs:
	def div (sele, x, y):
		return x // y

server.register_instance (MyFuncs())

def sleep_func(x):
	import time
	time.sleep(x)
	return 'done'

server.register_function (sleep_func, 'sleep')

server.serve_forever()
