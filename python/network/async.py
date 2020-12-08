import inspect
import asyncore, socket

class Echo (asyncore.dispatcher):

    def handle_connect (self, *args):
        print '=== %s::%s %s ===' % (self.name, inspect.stack()[0][3], args)

    def handle_accept (self, *args):
        print '=== %s::%s %s ===' % (self.name, inspect.stack()[0][3], args)
        sock, addr = self.accept()
        handler = EchoHandler (sock)

    def handle_close (self, *args):
        print '=== %s::%s %s ===' % (self.name, inspect.stack()[0][3], args)
        self.close ()

 
class EchoServer (Echo):
    def __init__ (self, host, port):
        asyncore.dispatcher.__init__ (self)
        self.create_socket (socket.AF_INET, socket.SOCK_STREAM)
        self.set_reuse_addr ()
        self.bind ((host, port))
        self.listen (5)
        self.name = 'EchoServer'

class EchoHandler (Echo):
    def __init__ (self, sock):
        asyncore.dispatcher.__init__ (self, sock)
        self.name = 'EchoHandler'

#    def handle_write (self, *args):
#        print '=== %s::%s %s ===' % (self.name, inspect.stack()[0][3], args)

    def handle_read (self, *args):
        print '=== %s::%s %s ===' % (self.name, inspect.stack()[0][3], args)
        while 1:
            try:
                data = self.recv (8192)
            except Exception as e:
                print e
                break
            self.send (data)


#    def readable (self, *args):
#        print '=== %s::%s %s ===' % (self.name, inspect.stack()[0][3], args)
#        r = asyncore.dispatcher.readable (self)
#        return r


#   def writable (self, *args):
#        print '=== %s::%s %s ===' % (self.name, inspect.stack()[0][3], args)
#        r = asyncore.dispatcher.writable (self)
#        return r

server = EchoServer ('localhost', 8080)
asyncore.loop()
