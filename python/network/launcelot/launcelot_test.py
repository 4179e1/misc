'''
During load test, it's likely to get the following error:
[Errno 99] Cannot assign requested address 

Which is caused by TIME_WAIT.

There's a effcient way to recycle TIME_WAIT, but with potencial risks:
# echo 1 > /proc/sys/net/ipv4/tcp_tw_recycle
'''

from funkload.FunkLoadTestCase import FunkLoadTestCase
import socket, os, unittest, launcelot

SERVER_HOST = os.environ.get('LAUNCELOG_SERVER', 'localhost')

import syslog

class TestLauncelot (FunkLoadTestCase):
	def test_dialog (self):
		sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		sock.connect ((SERVER_HOST, launcelot.PORT))
		for i in range(3):
			for k, v in launcelot.qadict.items():
				sock.sendall (k)
				reply = launcelot.recv_until(sock, '.')
				self.assertEqual (reply, v)
		sock.close()

if __name__ == '__main__':
	unittest.main()
