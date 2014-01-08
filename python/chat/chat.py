import socket, asyncore
import asynchat

PORT = 5005
NAME = 'TestChat'

class ChatSession (asynchat.async_chat):
    def __init__ (self, server, sock):
        asynchat.async_chat.__init__ (self, sock)
        self.set_terminator ('\r\n')
        self.server = server
        self.data = []
        self.push ('Welcome to %s\r\n' % self.server.name)

    def collect_incoming_data (self, data):
        self.data.append (data)

    def found_terminator (self):
        line = ''.join(self.data)
        if line:
            self.server.broadcast (self, line)
            self.data = []

    def handle_close (self):
        asynchat.async_chat.handle_close(self)
        self.server.disconnect (self)

class ChatServer (asyncore.dispatcher):
    def __init__ (self, port, name):
        asyncore.dispatcher.__init__(self)
        self.create_socket (socket.AF_INET, socket.SOCK_STREAM)
        self.set_reuse_addr()
        self.bind(('', port))
        self.listen (5)
        self.sessions = []
        self.name = name

    def disconnect (self, session):
        self.sessions.remove (session)

    def broadcast (self, current_session, line):
        for session in self.sessions:
            if session is not current_session:
                session.push (line + '\r\n')

    def handle_accept (self):
        conn, addr = self.accept ()
        print 'Connection attempt from', addr[0]
        self.sessions.append (ChatSession(self, conn))

if __name__ == '__main__':
    s = ChatServer(PORT, NAME)
    try: asyncore.loop()
    except KeyboardInterrupt: pass

