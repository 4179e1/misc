import signal, os
import threading
import sock

loop = 1

def sigint_handler (signum, arg):
	print 'Signal handler called with signal %d' % signum
	global loop
	loop = 0

if __name__ == '__main__':

	server = sock.MyServer (('localhost', 1234), sock.MyTCPHandler)

	thread = threading.Thread (target=server.serve_forever)
	thread.daemon = True
	thread.start()

	signal.signal (signal.SIGINT, sigint_handler)
	while loop:
		signal.pause()
		print loop
	
	print 'exiting'
	server.shutdown()
	thread.join()
