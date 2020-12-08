from twisted.internet.protocol import Protocol, ServerFactory
from twisted.internet import reactor
import launcelot

class Launcelot (Protocol):
	def connectionMade (self):
		self.question = ''
	def dataReceived (self, data):
		self.question += data.strip('\n')
		if self.question.endswith ('?'):
			self.transport.write (launcelot.qadict.get(self.question, "I don't understand your question."))
			self.question =''

factory = ServerFactory()
factory.protocol = Launcelot
reactor.listenTCP (1234, factory)
reactor.run()
