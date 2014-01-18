from funkload.FunkLoadTestCase import FunkLoadTestCase
import socket, os, unittest, launcelot

SERVER_HOST = os.environ.get('LAUNCELOG_SERVER', 'localhost')

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
