from SocketServer import ThreadingMixIn, TCPServer, BaseRequestHandler
import launcelot, simple, socket

class MyHandler (BaseRequestHandler):
	def handle(self):
		simple.handle_client(self.request)

class MyServer (ThreadingMixIn, TCPServer):
	allow_reuse_address = 1

server = MyServer(('', launcelot.PORT), MyHandler)
server.serve_forever()
