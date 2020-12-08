import SocketServer

class MyTCPHandler(SocketServer.BaseRequestHandler):
	def handle(self):
		while True:
			data = self.request.recv(1024).strip()
			if not data:
				break
			print data
			self.request.sendall(data.upper())

class MyServer (SocketServer.ThreadingMixIn, SocketServer.TCPServer):
	allow_reuse_address = 1
