import threading

class SockThread (threading.Thread):
	def __init__ (self, server):
		threading.Thread.__init__(self)
		self.daemon = True
		self.server = server

	def run (self):
		self.server.serve_forever()
		
