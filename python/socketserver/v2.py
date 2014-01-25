import signal, os
import sock
import sockthread

loop = 1

def sigint_handler (signum, arg):
	print 'Signal handler called with signal %d' % signum
	global loop
	loop = 0

if __name__ == '__main__':

	server = sock.MyServer (('localhost', 1234), sock.MyTCPHandler)

	thread = sockthread.SockThread (server)
	thread.start()

	signal.signal (signal.SIGINT, sigint_handler)
	while loop:
		signal.pause()
		print loop
	
	server.shutdown()
	thread.join()
